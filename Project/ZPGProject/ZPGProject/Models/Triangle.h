/**
 * @file Triangle.h
 *
 * @brief Triangle model
 *
 * @details  Command for rendering
 *           glDrawArrays(GL_TRIANGLES, 0, 144);
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

const float triangleVertexData[144] = {
	// back 
	-.5f, -.5f, .5f, 1, 1.0f, .0f, .0f, 1,
	.0f, .5f, .0f, 1, 1.0f, .0f, .0f, 1,
	.5f, -.5f, .5f, 1, 1.0f, .0f, .0f, 1,
	// left
	-.5f, -.5f, .5f, 1, .0f, 1.0f, .0f, 1,
	-.5f, -.5f, -.5f, 1, .0f, 1.0f, .0f, 1,
	.0f, .5f, .0f, 1, .0f, 1.0f, .0f, 1,
	// right
	.5f, -.5f, .5f, 1, .0f, .0f, 1.0f, 1,
	.5f, -.5f, -.5f, 1, .0f, .0f, 1.0f, 1,
	.0f, .5f, .0f, 1, .0f, .0f, 1.0f, 1,
	// bottom
	.5f, -.5f, .5f, 1, .0f, 1.0f, 1.0f, 1,
	-.5f, -.5f, .5f, 1, .0f, 1.0f, 1.0f, 1,
	-.5f, -.5f, -.5f, 1, .0f, 1.0f, 1.0f, 1,
	.5f, -.5f, .5f, 1, .0f, .5f, .5f, 1,
	.5f, -.5f, -.5f, 1, .0f, .5f, .5f, 1,
	-.5f, -.5f, -.5f, 1, .0f, .5f, .5f, 1,
	// front 
	-.5f, -.5f, -.5f, 1, 1.0f, .0f, 1.0f, 1,
	.0f, .5f, -.0f, 1, 1.0f, .0f, 1.0f, 1,
	.5f, -.5f, -.5f, 1, 1.0f, .0f, 1.0f, 1,
};