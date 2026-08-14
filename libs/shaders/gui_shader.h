#ifndef GuiShader_H
#define GuiShader_H

#include "shaderclass.h"
#include "glm/glm.hpp"

/**
  Classe che include le funzionalità specifiche legate agli shader da usare
  nell'applicazione. 
  Sono stati overloadati i metodi load_shaders e load_done.
  Sono stati inseriti due metodi pubblici per settare la matrice di trasformazione
  delle coordinate dei vertici. 
*/
class GuiShader : public ShaderClass {
  public:
    void set_model_transform(const glm::mat4 &transform);
    void set_texture_sampler(std::string location_name, int sampler_id);

  private:

    /**
        Metodo per il caricamento degli shader

        @return true se il caricamento è andato a buon fine
    */
    virtual bool load_shaders();

    /**
        Metodo che recupera tutte le location delle variabili uniform 
        negli shader caricati.  

        @return se le operazioni post-load sono andate a buon fine
    */
    virtual bool load_done();

    GLint _model_transform_location;
    GLint _bitmap_font_sampler_location;
};
#endif