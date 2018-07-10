#include "Engine\ArrayObject.h"

namespace engine {

    ArrayObject::ArrayObject() :
        m_vao{ 0 }
    {
        glGenVertexArrays(1, &m_vao);
    }

}