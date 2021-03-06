/*
 *  Copyright (C) 2017-2018 Team Kodi
 *  This file is part of Kodi - https://kodi.tv
 *
 *  SPDX-License-Identifier: GPL-2.0-or-later
 *  See LICENSES/README.md for more information.
 */

#pragma once

#include "cores/RetroPlayer/rendering/RenderSettings.h"
#include "cores/GameSettings.h"
#include "utils/Geometry.h"

extern "C" {
#include "libavutil/pixfmt.h"
}

#include <array>
#include <memory>
#include <stdint.h>

namespace KODI
{
namespace SHADER
{
  class IVideoShaderPreset;
}

namespace RETRO
{
  class CRenderContext;
  class IRenderBuffer;
  class IRenderBufferPool;

  class CRPBaseRenderer
  {
  public:
    CRPBaseRenderer(const CRenderSettings &renderSettings, CRenderContext &context, std::shared_ptr<IRenderBufferPool> bufferPool);
    virtual ~CRPBaseRenderer();

    /*!
     * \brief Get the buffer pool used by this renderer
     */
    IRenderBufferPool *GetBufferPool() { return m_bufferPool.get(); }

    // Player functions
    bool Configure(AVPixelFormat format);
    void FrameMove();
    /*!
     * \brief Performs whatever necessary before rendering the frame
     */
    void PreRender(bool clear);
    void SetBuffer(IRenderBuffer *buffer);
    void RenderFrame(bool clear, uint8_t alpha);
    void SetSpeed(double speed);

    // Feature support
    virtual bool Supports(RENDERFEATURE feature) const = 0;
    virtual bool Supports(SCALINGMETHOD method) const = 0;
    bool IsCompatible(const CRenderVideoSettings &settings) const;
    virtual SCALINGMETHOD GetDefaultScalingMethod() const = 0;

    // Public renderer interface
    virtual void Flush();
    virtual void Deinitialize() { }

    // Get render settings
    const CRenderSettings &GetRenderSettings() const { return m_renderSettings; }

    // Set render settings
    void SetShaderPreset(const std::string &presetPath);

    void SetScalingMethod(SCALINGMETHOD method);
    void SetViewMode(VIEWMODE viewMode);
    void SetRenderRotation(unsigned int rotationDegCCW);

    bool IsVisible() const;

  protected:
    // Protected renderer interface
    virtual bool ConfigureInternal() { return true; }
    virtual void RenderInternal(bool clear, uint8_t alpha) = 0;
    virtual void FlushInternal() { }

    // Construction parameters
    CRenderContext &m_context;
    std::shared_ptr<IRenderBufferPool> m_bufferPool;

    // Stream properties
    bool m_bConfigured = false;
    AVPixelFormat m_format = AV_PIX_FMT_NONE;

    // Rendering properties
    CRenderSettings m_renderSettings;
    IRenderBuffer *m_renderBuffer = nullptr;

    // Geometry properties
    CRect m_sourceRect;
    std::array<CPoint, 4> m_rotatedDestCoords{};

    // ====== Video Shader Members =====
    void UpdateVideoShaders();
    std::unique_ptr<SHADER::IVideoShaderPreset> m_shaderPreset;

    bool m_shadersNeedUpdate;
    bool m_bUseShaderPreset;

  private:
    /*!
     * \brief Calculate driven dimensions
     */
    virtual void ManageRenderArea(const IRenderBuffer &renderBuffer);

    /*!
     * \brief Performs whatever nessesary after a frame has been rendered
     */
    void PostRender();

    void MarkDirty();

    // Utility functions
    void GetScreenDimensions(float &screenWidth, float &screenHeight, float &screenPixelRatio);

    uint64_t m_renderFrameCount = 0;
    uint64_t m_lastRender = 0;
  };
}
}
