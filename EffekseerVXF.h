#pragma once

#include <memory>
#include <filesystem>


#pragma warning(disable:4100) // 'identifier' : unreferenced formal parameter
#include "Effekseer.h" // Effekseer must set both "include" and "Effekseer" directory
#include "EffekseerRendererDX11.h"
#pragma warning(pop)
#ifdef _DEBUG
#pragma comment(lib, "Effekseerd.lib")
#pragma comment(lib, "EffekseerRendererDX11d.lib")
#else
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")
#endif
#include <DirectXMath.h>

namespace EFFEKSEERLIB {
    //全体で使うEffekseerのマネージャやレンダラなどのデータ
    using RendererRef = EffekseerRendererDX11::RendererRef;


    inline void RendererInit(RendererRef renderer, ID3D11Device* dev, ID3D11DeviceContext* dc, int max_square) {
        renderer = EffekseerRendererDX11::Renderer::Create(dev, dc, max_square);
    }

    inline void ManagerInit(Effekseer::ManagerRef manager, const RendererRef& renderer, int max_square) {
        manager = Effekseer::Manager::Create(max_square);
        manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

        manager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
        manager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
        manager->SetRingRenderer(renderer->CreateRingRenderer());
        manager->SetTrackRenderer(renderer->CreateTrackRenderer());
        manager->SetModelRenderer(renderer->CreateModelRenderer());

        manager->SetTextureLoader(renderer->CreateTextureLoader());
        manager->SetModelLoader(renderer->CreateModelLoader());
        manager->SetMaterialLoader(renderer->CreateMaterialLoader());
        manager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
    }

    //個別のデータ保持用

    class EFKData
    {
    public:

        EFKData(std::string_view file_path)
            : m_filePath(file_path)
        {}
        EFKData(const Effekseer::ManagerRef& manager, std::string_view file_path)
            : m_filePath(file_path)
        {
            Load(manager);
        }

        void Load(const Effekseer::ManagerRef& manager) {
            if (std::filesystem::is_regular_file(m_filePath)) {
                std::filesystem::path filepath(m_filePath);
                m_effectRef = Effekseer::Effect::Create(manager, filepath.u16string().c_str());
            }
        }

        const std::string& GetFilePath() const noexcept {
            return m_filePath.string();
        }

        const Effekseer::EffectRef& GetEffectRef() const noexcept {
            return m_effectRef;
        }

    private:

        const std::filesystem::path m_filePath;
        Effekseer::EffectRef m_effectRef;

    };

    struct EffectTransform {
        DirectX::XMMATRIX matrix;
        bool                        isLoop = false;
        float                       speed = 1.0f;
        int                         maxFrame = 0;
    };

    class EffectInstance
    {
    public:

        EffectInstance(const std::shared_ptr<EFKData>& effect_data)
            : m_spEffectData(effect_data)
        {}

        std::shared_ptr<const EFKData> GetEffectData() const noexcept {
            return m_spEffectData;
        }

        double                           elapsedTime = 0;
        Effekseer::Handle                handle = 0;
        std::shared_ptr<EffectTransform> effectTransform;

    private:

        const std::shared_ptr<EFKData> m_spEffectData;

    };

}
