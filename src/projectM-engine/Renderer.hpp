#ifndef Renderer_HPP
#define Renderer_HPP

#include "PBuffer.hpp"
#include "PresetFrameIO.hpp"
#include "BeatDetect.hpp"
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#ifdef USE_FTGL
#include <FTGL/FTGL.h>
#include <FTGL/FTGLPixmapFont.h>
#include <FTGL/FTGLPolygonFont.h>
#endif /** USE_FTGL */

class BeatDetect;
class TextureManager;

class Renderer
{
  RenderTarget *renderTarget;
  BeatDetect *beatDetect;
  TextureManager *textureManager;

  //per pixel equation variables
  float **gridx;  //grid containing interpolated mesh 
  float **gridy;
  float **origx2;  //original mesh 
  float **origy2;
  int gx;
  int gy;

  int vw; 
  int vh;
   
    float aspect;
 

  
 public:
 

#ifdef USE_FTGL
FTGLPixmapFont *title_font;
FTGLPixmapFont *other_font;
FTGLPolygonFont *poly_font;
#endif /** USE_FTGL */
 
 int showfps;
    int showtitle;
    int showpreset;
    int showhelp;
    int showstats;

    int studio;
    int correction;

  std::string fontURL;
 
    int noSwitch;

    int totalframes;
float realfps;
char *title;
    int drawtitle;

  Renderer( int width, int height, int gx, int gy, RenderTarget *renderTarget, TextureManager *textureManager, BeatDetect *beatDetect, std::string fontURL);
  ~Renderer();
  void RenderFrame(PresetOutputs *presetOutputs, PresetInputs *presetInputs);
  void reset(int w, int h);
  GLuint initRenderToTexture();
  void PerPixelMath(PresetOutputs *presetOutputs,  PresetInputs *presetInputs);
  void WaveformMath(PresetOutputs *presetOutputs, PresetInputs *presetInputs, bool isSmoothing);

 	void setPresetName(const std::string& theValue)
	{
	  m_presetName = theValue;
	}
	

	std::string presetName() const
	{
	  return m_presetName;
	}
	

private:

  std::string m_presetName;

  void draw_waveform(PresetOutputs * presetOutputs);
  void PerFrame(PresetOutputs *presetOutputs);
  void Interpolation(PresetOutputs *presetOutputs, PresetInputs *presetInputs);

  void rescale_per_pixel_matrices();
  void maximize_colors(PresetOutputs *presetOutputs);
  void render_texture_to_screen(PresetOutputs *presetOutputs);
  void render_texture_to_studio(PresetOutputs *presetOutputs, PresetInputs *presetInputs);
  void draw_fps( float realfps );
  void draw_stats(PresetInputs *presetInputs);
  void draw_help( );
  void draw_preset();
  void draw_title();
  void draw_title_to_screen();
  void maximize_colors();
  void draw_title_to_texture();
  void draw_motion_vectors(PresetOutputs *presetOutputs);
  void draw_borders(PresetOutputs *presetOutputs);
  void draw_shapes(PresetOutputs *presetOutputs);
  void draw_custom_waves(PresetOutputs *presetOutputs);

  void modulate_opacity_by_volume(PresetOutputs *presetOutputs) ;
  void darken_center();
};

#endif
