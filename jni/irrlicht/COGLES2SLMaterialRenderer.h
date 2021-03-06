// Copyright (C) 2009-2010 Amundis
// Heavily based on the OpenGL driver implemented by Nikolaus Gebhardt
// and OpenGL ES driver implemented by Christian Stehno
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in Irrlicht.h
#ifndef __C_OGLES2_SL_MATERIAL_RENDERER_H_INCLUDED__
#define __C_OGLES2_SL_MATERIAL_RENDERER_H_INCLUDED__

#include "IrrCompileConfig.h"
#ifdef _IRR_COMPILE_WITH_OGLES2_

#include "IMaterialRenderer.h"
#include "IMaterialRendererServices.h"
#include "IGPUProgrammingServices.h"
#include "irrArray.h"
#include "irrString.h"

namespace irr
{
    namespace io
    {
        class IFileSystem;
    }
    namespace video
    {

        class COGLES2Driver;
        class IShaderConstantSetCallBack;

//! Class for using GLSL shaders with OpenGL
//! Please note: This renderer implements its own IMaterialRendererServices
        class COGLES2SLMaterialRenderer : public IMaterialRenderer, public IMaterialRendererServices
        {
		private:
			static const char* const sDefaultUniformNames[];
			enum DEF_SHADER_UNIFORM
            {
				DEF_RENDER_MODE = 0,
                DEF_MVP_MATRIX,
                DEF_WORLD_MATRIX,
                DEF_NORMALIZE,
                DEF_EYE_POSITION,
                DEF_USE_LIGHT,
                DEF_LIGHT_POSITION,
                DEF_LIGHT_AMBIENT,
                DEF_LIGHT_DIFFUSE,
                DEF_LIGHT_SPECULAR,
                DEF_LIGHT_DIRECTION,
                DEF_LIGHT_ATTENUATION,
                DEF_LIGHT_EXPONENT,
                DEF_LIGHT_CUTOFF,
                DEF_AMBIENT_COLOR,
                DEF_LIGHTING,
                DEF_MATERIAL_AMBIENT,
                DEF_MATERIAL_EMISSION,
                DEF_MATERIAL_DIFFUSE,
                DEF_MATERIAL_SPECULAR,
                DEF_MATERIAL_SHININESS,
                DEF_COLOR_MATERIAL,
                DEF_USE_TEXTURE,
                DEF_TEXTURE_MATRIX,
                DEF_USE_TEXTURE_MATRIX,
                DEF_CLIP,
                DEF_CLIP_PLANE,
                DEF_ALPHA_TEST,
                DEF_ALPHA_VALUE,
                DEF_FOG,
                DEF_FOG_TYPE,
                DEF_FOG_COLOR,
                DEF_FOG_START,
                DEF_FOG_END,
                DEF_FOG_DENSITY,
                DEF_TEXTURE_UNIT0,
                DEF_TEXTURE_UNIT1,
				DEF_UTIMER,
                DEF_UNIFORM_COUNT
            };


        protected:
            struct SUniformInfo
            {
                u32 type;
                s32 location;
				irr::core::stringc name;
            };
            typedef SUniformInfo SAttributeInfo;
        public:

            //! Constructor
            COGLES2SLMaterialRenderer(
                COGLES2Driver* driver,
                s32& outMaterialTypeNr,
                const c8* vertexShaderProgram,
                const c8* pixelShaderProgram,
                IShaderConstantSetCallBack* callback,
                IMaterialRenderer* baseMaterial,
                s32 userData );

            //! Destructor
            virtual ~COGLES2SLMaterialRenderer();

            virtual void OnSetMaterial( const SMaterial& material, const SMaterial& lastMaterial,
                                        bool resetAllRenderstates, IMaterialRendererServices* services );

            virtual bool OnRender( IMaterialRendererServices* service, E_VERTEX_TYPE vtxtype );
            virtual bool PostRender( IMaterialRendererServices* service, E_VERTEX_TYPE vtxtype );

            virtual void OnUnsetMaterial();

            //! Returns if the material is transparent.
            virtual bool isTransparent() const;

            // implementations for the render services
            virtual void setBasicRenderStates( const SMaterial& material, const SMaterial& lastMaterial, bool resetAllRenderstates );
            virtual bool setVertexShaderConstant( const c8* name, const f32* floats, int count );
            virtual void setVertexShaderConstant( const f32* data, s32 startRegister, s32 constantAmount = 1 );
            virtual bool setPixelShaderConstant( const c8* name, const f32* floats, int count );
            virtual void setPixelShaderConstant( const f32* data, s32 startRegister, s32 constantAmount = 1 );

            bool setUniform( int index, const void* data, int count = 1 );

            virtual bool setVertexShaderPointer( const c8* name, const void* pointer, s32 size = 3, bool normalized = false, u16 stride = 0 );
            virtual void enableVertexShaderPointer( const c8* name );
            virtual void disableVertexShaderPointer( const c8* name );

            bool setTextureUnit( const c8* name, int unit );

            virtual bool enableMaterialTexture( const c8* name, int materialId );
            virtual bool disableMaterialTexture( int materialId );

            virtual IVideoDriver* getVideoDriver();

            void useProgram();

        protected:

            //! constructor only for use by derived classes who want to
            //! create a fall back material for example.
            COGLES2SLMaterialRenderer( COGLES2Driver* driver,
                                       io::IFileSystem* fs,
                                       IShaderConstantSetCallBack* callback,
                                       IMaterialRenderer* baseMaterial,
                                       const char* const* uniformStringTable,
                                       const u32& uniformCount,
                                       s32 userData = 0 );

            void init( s32& outMaterialTypeNr,
                       const c8* vertexShaderProgram,
                       const c8* pixelShaderProgram,
                       bool registerMaterial = true );

            void initFromFiles( s32& outMaterialTypeNr,
                                const c8* vertexShaderFile,
                                const c8* pixelShaderFile,
                                bool registerMaterial = true );

            void reloadFromFiles( const c8* vertexShaderFile,
                                  const c8* pixelShaderFile );

            bool readVertexShader( const c8* vertexShaderFile );
            bool readFragmentShader( const c8* fragmentShaderFile );
            bool readShader( u32 shaderType, const c8* shaderFile );

            bool createProgram();
            bool createShader( u32 shaderType, const char* shader, const char* shaderFile );
            bool linkProgram();

            COGLES2Driver* Driver;
            IShaderConstantSetCallBack* CallBack;
            IMaterialRenderer* BaseMaterial;
            io::IFileSystem* FileSystem;

            u32 Program;

            core::array<SUniformInfo> UniformInfo;
            core::array<SAttributeInfo> AttributeInfo;
            s32 UserData;

            const char* const* UniformStringTable;
            const int    UniformCount;
        };

    } // end namespace video


} // end namespace irr

#endif //_IRR_COMPILE_WITH_OPENGLES2_
#endif //__C_OPEN_GL_ES2_SL_MATERIAL_RENDERER_H_INCLUDED__
