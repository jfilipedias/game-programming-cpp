#pragma once

class VertexArray {
public:
    VertexArray(const float* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices);
    ~VertexArray();

    void SetActive();

    unsigned int GetNumVerts() const { return mNumVerts; }
    unsigned int GetNumIndicies() const { return mNumIndicies; }

private:
    unsigned int mNumVerts;
    unsigned int mNumIndicies;
    unsigned int mVertexBufferId;
    unsigned int mIndexBufferId;
    unsigned int mVertexArrayId;
};
