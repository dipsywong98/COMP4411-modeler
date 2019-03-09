#pragma once
#include "modelerview.h"
// The sample model.  You should build a file
// very similar to this for when you make your model.
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include "modelerglobals.h"

// To make a MyModel, we inherit off of ModelerView
class MyModel : public ModelerView
{
public:
	MyModel(int x, int y, int w, int h, char *label)
		: ModelerView(x, y, w, h, label) { }

	virtual void draw();
	void drawArm(int levels, int curDept = 0);
	void drawClamp();
};