#include "renderer.h"
#include <fstream>
#include <sstream>

using namespace agl;
using namespace glm;
using namespace std;

static void PrintShaderErrors(GLuint id, const std::string label)
{
   std::cerr << label << " failed\n";
   GLint logLen;
   glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLen);
   if (logLen > 0)
   {
      char* log = (char*)malloc(logLen);
      GLsizei written;
      glGetShaderInfoLog(id, logLen, &written, log);
      std::cerr << "Shader log: " << log << std::endl;
      free(log);
   }
}

Renderer::Renderer()
{
   mInitialized = false;
}

Renderer::~Renderer()
{
}

bool Renderer::initialized() const
{
   return mInitialized;
}


vec3 Renderer::cameraPosition() const
{
   return mLookfrom;
}

void Renderer::init(const std::string& vertex, const std::string& fragment)
{
   mInitialized = true;

   skybox = new SkyBox(10);

   const float positions[] =
   {
       0.0f, 0.0f, 0.0f,
       1.0f, 0.0f, 0.0f,
       0.0f, 1.0f, 0.0f,

       1.0f, 0.0f, 0.0f,
       1.0f, 1.0f, 0.0f,
       0.0f, 1.0f, 0.0f,
   };

   glGenBuffers(1, &mVboPosId);
   glBindBuffer(GL_ARRAY_BUFFER, mVboPosId);
   glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), positions, GL_STATIC_DRAW);

   glGenVertexArrays(1, &mVaoId);
   glBindVertexArray(mVaoId);

   glEnableVertexAttribArray(0); // 0 -> Sending VertexPositions to array #0 in the active shader
   glBindBuffer(GL_ARRAY_BUFFER, mVboPosId); // always bind before setting data
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLubyte*)NULL);

   mShaderId = loadShader(vertex, fragment);

   glActiveTexture(GL_TEXTURE1);
   vector<string> faces = { "../textures/skybox/right.png", "../textures/skybox/left.png", "../textures/skybox/front.png",
                            "../textures/skybox/back.png", "../textures/skybox/top.png", "../textures/skybox/bottom.png" };

   GLuint cubemapID = loadCubemap(faces);
   glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
   faces.clear();
}

void Renderer::blendMode(BlendMode mode)
{
   if (mode == ADD)
   {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE);// Additive blend
   }
   else if (mode == ALPHA)
   {
      glEnable(GL_BLEND);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Alpha blend
   }
   else
   {
      glDisable(GL_BLEND);
   }
}

void Renderer::perspective(float fovRadians, float aspect, float near, float far)
{
   mProjectionMatrix = glm::perspective(fovRadians, aspect, near, far);
}

void Renderer::ortho(float minx, float maxx, float miny, float maxy, float minz, float maxz)
{
   mProjectionMatrix = glm::ortho(minx, maxx, miny, maxy, minz, maxz);
}

void Renderer::lookAt(const vec3& lookfrom, const vec3& lookat)
{
   mLookfrom = lookfrom;
   mViewMatrix = glm::lookAt(lookfrom, lookat, vec3(0,1,0));
}

void Renderer::begin(GLuint texIf, BlendMode mode)
{
   assert(mInitialized);

   glUseProgram(mShaderId);
   blendMode(mode);

   mat4 mvp = mProjectionMatrix * mViewMatrix;
   glUniformMatrix4fv(glGetUniformLocation(mShaderId, "uVP"), 1, GL_FALSE, &mvp[0][0]);
   glUniform3f(glGetUniformLocation(mShaderId, "uCameraPos"), mLookfrom[0], mLookfrom[1], mLookfrom[2]);
   
   glActiveTexture(GL_TEXTURE1);
   glUniform1i(glGetUniformLocation(mShaderId, "cubemap"), 1);
   glUniform1i(glGetUniformLocation(mShaderId, "DrawSkyBox"), 1);
   skybox->render();
   
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, texIf);
   glUniform1i(glGetUniformLocation(mShaderId, "DrawSkyBox"), 0);
   glUniform1i(glGetUniformLocation(mShaderId, "image"), 0);

   glBindVertexArray(mVaoId);
   glEnableVertexAttribArray(0); // 0 -> Sending VertexPositions to array #0 in the active shader
}

void Renderer::quad(const glm::vec3& pos, const glm::vec4& color, float size)
{
   assert(mInitialized);
   glUniform3f(glGetUniformLocation(mShaderId, "uOffset"), pos[0], pos[1], pos[2]);
   glUniform4f(glGetUniformLocation(mShaderId, "uColor"), color[0], color[1], color[2], color[3]);
   glUniform1f(glGetUniformLocation(mShaderId, "uSize"), size);

   glDrawArrays(GL_TRIANGLES, 0, 6); 
}

void Renderer::end()
{
   assert(mInitialized);
   glUseProgram(0);
}


GLuint Renderer::loadTexture(const std::string& filename)
{
   Image image;
   image.load(filename);

   glEnable(GL_TEXTURE0);
   glActiveTexture(GL_TEXTURE0);

   GLuint texId;
   glGenTextures(1, &texId);
   glBindTexture(GL_TEXTURE_2D, texId);
   glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, image.width(), image.height());
   glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.width(), image.height(),
      GL_RGBA, GL_UNSIGNED_BYTE, image.data());

   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   return texId;
}

GLuint Renderer::loadCubemap(vector<std::string> faces)
{
    glEnable(GL_TEXTURE1);
    glActiveTexture(GL_TEXTURE1);

    GLuint texId;
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texId);

    GLuint targets[] = {
        GL_TEXTURE_CUBE_MAP_POSITIVE_X,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
        GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
        GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
    };

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        Image image;
        image.load(faces[i]);
        unsigned char* data = image.data();
        if (data)
        {
            glTexImage2D(targets[i],
                0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data
            );
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return texId;
}

std::string Renderer::loadShaderFromFile(const std::string& fileName)
{
   std::ifstream file(fileName);
   if (!file)
   {
      std::cout << "Cannot load file: " << fileName << std::endl;
      return "";
   }

   std::stringstream code;
   code << file.rdbuf();
   file.close();

   return code.str();
}

GLuint Renderer::loadShader(const std::string& vertex, const std::string& fragment)
{
   GLint result;
   std::string vertexShader = loadShaderFromFile(vertex);
   const char* vertexShaderRaw = vertexShader.c_str();
   GLuint vshaderId = glCreateShader(GL_VERTEX_SHADER);
   glShaderSource(vshaderId, 1, &vertexShaderRaw, NULL);
   glCompileShader(vshaderId);
   glGetShaderiv(vshaderId, GL_COMPILE_STATUS, &result);
   if (result == GL_FALSE)
   {
      PrintShaderErrors(vshaderId, "Vertex shader");
      return -1;
   }

   std::string fragmentShader = loadShaderFromFile(fragment);
   const char* fragmentShaderRaw = fragmentShader.c_str();
   GLuint fshaderId = glCreateShader(GL_FRAGMENT_SHADER);
   glShaderSource(fshaderId, 1, &fragmentShaderRaw, NULL);
   glCompileShader(fshaderId);
   glGetShaderiv(fshaderId, GL_COMPILE_STATUS, &result);
   if (result == GL_FALSE)
   {
      PrintShaderErrors(fshaderId, "Fragment shader");
      return -1;
   }

   GLuint shaderId = glCreateProgram();
   glAttachShader(shaderId, vshaderId);
   glAttachShader(shaderId, fshaderId);
   glLinkProgram(shaderId);
   glGetShaderiv(shaderId, GL_LINK_STATUS, &result);
   if (result == GL_FALSE)
   {
      PrintShaderErrors(shaderId, "Shader link");
      return -1;
   }
   return shaderId;
}

// For rendering animated sprites
   //glUniform1f(glGetUniformLocation(shaderId, "uRows"), 4);
   //glUniform1f(glGetUniformLocation(shaderId, "uCols"), 8);
   //glUniform1f(glGetUniformLocation(shaderId, "uTime"), 0);
   //glUniform1f(glGetUniformLocation(shaderId, "uTimeOffset"), 0);

