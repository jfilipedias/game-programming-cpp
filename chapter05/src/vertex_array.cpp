#include "vertex_array.h"
#include <glad/gl.h>

VertexArray::VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices)
    : mNumVerts(numVerts),
      mNumIndicies(numIndices) {
    // Create vertex array
    glad_glGenVertexArrays(1, &mVertexArrayId);
    glad_glBindVertexArray(mVertexArrayId);

    // Create vertex buffer
    glad_glGenBuffers(1, &mVertexBufferId);
    glad_glBindBuffer(GL_ARRAY_BUFFER, mVertexBufferId);
    glad_glBufferData(GL_ARRAY_BUFFER, numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW);

    // Create index buffer
    glad_glGenBuffers(1, &mIndexBufferId);
    glad_glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBufferId);
    glad_glBufferData(GL_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glad_glEnableVertexAttribArray(0);
    glad_glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glad_glEnableVertexAttribArray(1);
    glad_glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));
}

VertexArray::~VertexArray() {
    glad_glDeleteBuffers(1, &mVertexBufferId);
    glad_glDeleteBuffers(1, &mIndexBufferId);
    glad_glDeleteVertexArrays(1, &mVertexArrayId);
}

void VertexArray::SetActive() {
    glad_glBindVertexArray(mVertexArrayId);
}
