// generated by Fast Light User Interface Designer (fluid) version 1.00
#pragma warning( disable : 4786 )

#include "modelerui.h"
#include "modelerapp.h"

#include "camera.h"

#if _MSC_VER >= 1300

#include <iostream>

#else //  _MSC_VER >= 1300

#include <iostream.h>

#endif // _MSC_VER >= 1300

#include <string>
#include <fstream>
using namespace std;

inline void ModelerUserInterface::cb_m_controlsWindow_i(Fl_Window*, void*) {
  0;;
}
void ModelerUserInterface::cb_m_controlsWindow(Fl_Window* o, void* v) {
  ((ModelerUserInterface*)(o->user_data()))->cb_m_controlsWindow_i(o,v);
}

inline void ModelerUserInterface::cb_Save_i(Fl_Menu_*, void*) {
  char *filename = NULL;
filename = fl_file_chooser("Save RAY File", "*.ray", NULL);
if (filename)
{
	if (openRayFile(filename) == false)
		fl_alert("Error opening file.");
	else
	{
		m_modelerView->draw();
		closeRayFile();
	}
};
}
void ModelerUserInterface::cb_Save(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_Save_i(o,v);
}

inline void ModelerUserInterface::cb_Save1_i(Fl_Menu_*, void*) {
  char *filename = NULL;
filename = fl_file_chooser("Save BMP File", "*.bmp", NULL);
if (filename)
{
	int x = m_modelerView->x();
	int y = m_modelerView->y();
	int w = m_modelerView->w();
	int h = m_modelerView->h();

	m_modelerWindow->show();
//	do {Sleep(10); }
//	while (!m_modelerWindow->shown());
//	m_modelerView->draw();
	m_modelerView->make_current();
m_modelerView->draw();
	
		
	unsigned char *imageBuffer = new unsigned char[3*w*h];

        // Tell openGL to read from the front buffer when capturing
        // out paint strokes
        glReadBuffer(GL_BACK);

        glPixelStorei( GL_PACK_ALIGNMENT, 1 );
        glPixelStorei( GL_PACK_ROW_LENGTH, w );
        
        glReadPixels( 0, 0, w, h, 
                GL_RGB, GL_UNSIGNED_BYTE, 
                imageBuffer );


	writeBMP(filename, w,h, imageBuffer);

	delete [] imageBuffer;
};
}
void ModelerUserInterface::cb_Save1(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_Save1_i(o,v);
}

// IANLI
// Implementation callback for saving the positions of the model into a file
// The first line of the file contains the values for the position/orientation of
// the camera. The values are ordered as the following:
//		elevation azimuth dolly twist lookAtX lookAtY lookAtZ
// The lines after correspond to the values of the controls. The following lines 
// have this format:
//		controlNumber controlValue
inline void ModelerUserInterface::cb_SavePos_i(Fl_Menu_*, void*) {
	char *filename = NULL;
	filename = fl_file_chooser("Save .pos File", "*.pos", NULL);

	if (filename)
	{
		FILE* m_posFile = fopen(filename, "w");

		float elevation, azimuth, dolly, twist;
		Vec3f lookAt;
		elevation = m_modelerView->m_camera->getElevation();
		dolly = m_modelerView->m_camera->getDolly();
		azimuth = m_modelerView->m_camera->getAzimuth();
		twist = m_modelerView->m_camera->getTwist();
		lookAt = m_modelerView->m_camera->getLookAt();

		fprintf(m_posFile, "%f %f %f %f %f %f %f\n", elevation, azimuth, dolly, twist, lookAt[0], lookAt[1], lookAt[2]);

		double value;
		for(int i = 0; i < NUMCONTROLS; i++)
		{
			value = ModelerApplication::Instance()->GetControlValue(i);

			fprintf(m_posFile, "%d %f\n", i, value);
		}

		fclose(m_posFile);
	};
}
void ModelerUserInterface::cb_SavePos(Fl_Menu_* o, void* v) {
	((ModelerUserInterface*)(o->parent()->user_data()))->cb_SavePos_i(o,v);
}

inline void ModelerUserInterface::cb_OpenPos_i(Fl_Menu_*, void*) {
	char *filename = NULL;
	filename = fl_file_chooser("Open .pos File", "*.pos", NULL);

	if (filename)
	{
		ifstream ifs( filename );
		if( !ifs ) {
			cerr << "Error: couldn't read position file " << filename << endl;
			return;
		}

		float elevation, azimuth, dolly, twist, x, y, z;
		ifs >> elevation >> azimuth >> dolly >> twist >> x >> y >> z;
		
		m_modelerView->m_camera->setElevation( elevation);
		m_modelerView->m_camera->setAzimuth( azimuth );
		m_modelerView->m_camera->setDolly( dolly );
		m_modelerView->m_camera->setTwist( twist );
		m_modelerView->m_camera->setLookAt( Vec3f(x, y, z) );
		
		int controlNum; 
		float value;
		while( ifs >> controlNum >> value )
		{
			if( controlNum >= NUMCONTROLS ) {
				break;
			}
			
			ModelerApplication::Instance()->SetControlValue(controlNum, value);
		}

		m_modelerView->redraw();
	};
}
void ModelerUserInterface::cb_OpenPos(Fl_Menu_* o, void* v) {
	((ModelerUserInterface*)(o->parent()->user_data()))->cb_OpenPos_i(o,v);
}

inline void ModelerUserInterface::cb_Exit_i(Fl_Menu_*, void*) {
  m_controlsWindow->hide();
m_modelerWindow->hide();
}  
void ModelerUserInterface::cb_Exit(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_Exit_i(o,v);
}

inline void ModelerUserInterface::cb_Normal_i(Fl_Menu_*, void*) {
  setDrawMode(NORMAL);
m_modelerView->redraw();
}
void ModelerUserInterface::cb_Normal(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_Normal_i(o,v);
}

inline void ModelerUserInterface::cb_Flat_i(Fl_Menu_*, void*) {
  setDrawMode(FLATSHADE);
m_modelerView->redraw();
}
void ModelerUserInterface::cb_Flat(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_Flat_i(o,v);
}

inline void ModelerUserInterface::cb_Wireframe_i(Fl_Menu_*, void*) {
  setDrawMode(WIREFRAME);
m_modelerView->redraw();
}
void ModelerUserInterface::cb_Wireframe(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_Wireframe_i(o,v);
}

inline void ModelerUserInterface::cb_High_i(Fl_Menu_*, void*) {
  setQuality(HIGH);
m_modelerView->redraw();
}
void ModelerUserInterface::cb_High(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_High_i(o,v);
}

inline void ModelerUserInterface::cb_Medium_i(Fl_Menu_*, void*) {
  setQuality(MEDIUM);
m_modelerView->redraw();
}
void ModelerUserInterface::cb_Medium(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_Medium_i(o,v);
}

inline void ModelerUserInterface::cb_Low_i(Fl_Menu_*, void*) {
  setQuality(LOW);
m_modelerView->redraw();
}
void ModelerUserInterface::cb_Low(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_Low_i(o,v);
}

inline void ModelerUserInterface::cb_Poor_i(Fl_Menu_*, void*) {
  setQuality(POOR);
m_modelerView->redraw();
}
void ModelerUserInterface::cb_Poor(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_Poor_i(o,v);
}

// Callback function to look at origin again.
inline void ModelerUserInterface::cb_Focus_i(Fl_Menu_*, void*) {
	m_modelerView->m_camera->setLookAt( Vec3f(0, 0, 0) );
	m_modelerView->redraw();
}
void ModelerUserInterface::cb_Focus(Fl_Menu_* o, void* v) {
	((ModelerUserInterface*)(o->parent()->user_data()))->cb_Focus_i(o,v);
}

// Callback function to look at origin again.
inline void ModelerUserInterface::cb_FrameAll_i(Fl_Menu_*, void*) {
	m_modelerView->m_camera->frameAll();
	m_modelerView->redraw();
}
void ModelerUserInterface::cb_FrameAll(Fl_Menu_* o, void* v) {
	((ModelerUserInterface*)(o->parent()->user_data()))->cb_FrameAll_i(o,v);
}

inline void ModelerUserInterface::cb_m_controlsAnimOnMenu_i(Fl_Menu_*, void*) {
  ModelerApplication::Instance()->m_animating = (m_controlsAnimOnMenu->value() == 0) ? false : true;
}
void ModelerUserInterface::cb_m_controlsAnimOnMenu(Fl_Menu_* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_m_controlsAnimOnMenu_i(o,v);
}

Fl_Menu_Item ModelerUserInterface::menu_m_controlsMenuBar[] = {
 {"File", 0,  0, 0, 64, 0, 0, 14, 0},
 {"Save Raytracer File", 0,  (Fl_Callback*)ModelerUserInterface::cb_Save, 0, 0, 0, 0, 14, 0},
 {"Save Bitmap File", 0,  (Fl_Callback*)ModelerUserInterface::cb_Save1, 0, 128, 0, 0, 14, 0},
 {"Open Position File", 0, (Fl_Callback*)ModelerUserInterface::cb_OpenPos, 0, 0, 0, 0, 14, 0},
 {"Save Position File", 0, (Fl_Callback*)ModelerUserInterface::cb_SavePos, 0, 128, 0, 0, 14, 0},
 {"Exit", 0,  (Fl_Callback*)ModelerUserInterface::cb_Exit, 0, 0, 0, 0, 14, 0},
 {0},
 {"View", 0,  0, 0, 64, 0, 0, 14, 0},
 {"Normal", 0,  (Fl_Callback*)ModelerUserInterface::cb_Normal, 0, 12, 0, 0, 14, 0},
 {"Flat Shaded", 0,  (Fl_Callback*)ModelerUserInterface::cb_Flat, 0, 8, 0, 0, 14, 0},
 {"Wireframe", 0,  (Fl_Callback*)ModelerUserInterface::cb_Wireframe, 0, 136, 0, 0, 14, 0},
 {"High Quality", 0,  (Fl_Callback*)ModelerUserInterface::cb_High, 0, 8, 0, 0, 14, 0},
 {"Medium Quality", 0,  (Fl_Callback*)ModelerUserInterface::cb_Medium, 0, 12, 0, 0, 14, 0},
 {"Low Quality", 0,  (Fl_Callback*)ModelerUserInterface::cb_Low, 0, 8, 0, 0, 14, 0},
 {"Poor Quality", 0,  (Fl_Callback*)ModelerUserInterface::cb_Poor, 0, 136, 0, 0, 14, 0},
 {"Focus on Origin", 0,  (Fl_Callback*)ModelerUserInterface::cb_Focus, 0, 0, 0, 0, 14, 0},
 {"Frame All", 0,  (Fl_Callback*)ModelerUserInterface::cb_FrameAll, 0, 0, 0, 0, 14, 0},
 {0},
 {"Animate", 0,  0, 0, 64, 0, 0, 14, 0},
 //{"Enable", 0,  (Fl_Callback*)ModelerUserInterface::cb_m_controlsAnimOnMenu, 0, 2, 0, 0, 14, 0},
 {0},
 {0}
};
// 11-01-2001: fixed bug that caused animation problems
Fl_Menu_Item* ModelerUserInterface::m_controlsAnimOnMenu = ModelerUserInterface::menu_m_controlsMenuBar + 18;

inline void ModelerUserInterface::cb_m_controlsBrowser_i(Fl_Browser*, void*) {
  for (int i=0; i<ModelerApplication::Instance()->m_numControls; i++) {
	if (m_controlsBrowser->selected(i+1))
		ModelerApplication::Instance()->ShowControl(i);
	else
		ModelerApplication::Instance()->HideControl(i);
};
}
void ModelerUserInterface::cb_m_controlsBrowser(Fl_Browser* o, void* v) {
  ((ModelerUserInterface*)(o->parent()->user_data()))->cb_m_controlsBrowser_i(o,v);
}

inline void ModelerUserInterface::cb_m_modelerWindow_i(Fl_Window*, void*) {
  0;
}
void ModelerUserInterface::cb_m_modelerWindow(Fl_Window* o, void* v) {
  ((ModelerUserInterface*)(o->user_data()))->cb_m_modelerWindow_i(o,v);
}

ModelerUserInterface::ModelerUserInterface() {
  Fl_Window* w;
  { Fl_Window* o = m_controlsWindow = new Fl_Window(395, 326, "CS 341 Modeler (SP02)");
    w = o;
    o->callback((Fl_Callback*)cb_m_controlsWindow, (void*)(this));
    o->when(FL_WHEN_NEVER);
    { Fl_Menu_Bar* o = m_controlsMenuBar = new Fl_Menu_Bar(0, 0, 395, 25);
      o->menu(menu_m_controlsMenuBar);
    }
    { Fl_Browser* o = m_controlsBrowser = new Fl_Browser(0, 25, 140, 300, "Controls");
      o->type(3);
      o->textsize(10);
      o->callback((Fl_Callback*)cb_m_controlsBrowser);
      Fl_Group::current()->resizable(o);
    }
    { Fl_Scroll* o = m_controlsScroll = new Fl_Scroll(145, 25, 250, 300);
      o->type(6);
      o->when(FL_WHEN_CHANGED);
      { Fl_Pack* o = m_controlsPack = new Fl_Pack(145, 25, 225, 300);
        o->end();
      }
      o->end();
    }
    o->end();
  }
  { Fl_Window* o = m_modelerWindow = new Fl_Window(340, 296, "Model");
    w = o;
    o->callback((Fl_Callback*)cb_m_modelerWindow, (void*)(this));
    o->when(FL_WHEN_NEVER);
    { ModelerView* o = m_modelerView = new ModelerView(0, 0, 340, 295, "ModelerView");
      Fl_Group::current()->resizable(o);
    }
    o->end();
  }
}

void ModelerUserInterface::show() {
  m_controlsWindow->show();
m_modelerWindow->show();
m_modelerView->show();
}
