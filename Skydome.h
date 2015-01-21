//#include <gl\glut.h>
//
//
//class Skydome
//{
//public:
//    explicit Skydome( float fRadius = 1.0f, unsigned int uiSlices = 16, unsigned int uiStacks = 16 );
//    virtual ~Skydome();
//
//    void Init();
//    void Terminate();
//
//    bool LoadTexture( char *hFileName );
//    void Render();
//protected:
//
//private:
//    // The OpenGL resources
//    GLuint          m_GLTextureID;
//    GLUquadricObj*  m_QuadricObj;
//
//    float           m_fRadius;
//    unsigned int    m_uiSlices;
//    unsigned int    m_uiStacks;
//};