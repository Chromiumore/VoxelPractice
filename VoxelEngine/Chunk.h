#pragma once

#define CHUNK_WIDTH 32
#define CHUNK_HEIGHT 16
#define CHUNK_DEPTH 16
#define CHUNK_VOL (CHUNK_WIDTH * CHUNK_HEIGHT * CHUNK_DEPTH)

class voxel;

class Chunk
{
public:
	voxel* voxels;
	Chunk();
	~Chunk();
};

