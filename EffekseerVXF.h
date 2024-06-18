#pragma once

#include <memory>
#include <filesystem>
#include <string>
#include <string_view>
#include <unordered_map>
#include "Engine/camera.h"
#include <DirectXMath.h>
#include "Assert.h"

namespace fs = std::filesystem;

#pragma warning(disable:4100) // 'identifier' : unreferenced formal parameter
#include "Effekseer.h" // Effekseer must set both "include" and "Effekseer" directory
#include "EffekseerRendererDX11.h"


#ifdef _DEBUG
#pragma comment(lib, "Effekseerd.lib")
#pragma comment(lib, "EffekseerRendererDX11d.lib")
#else
#pragma comment(lib, "Effekseer.lib")
#pragma comment(lib, "EffekseerRendererDX11.lib")
#endif


namespace EFFEKSEERLIB {
    constexpr float DEFAULT_FRAME_RATE{ 60.0f };
    //全体で使うEffekseerのマネージャやレンダラなどのデータ
    using RendererRef = EffekseerRendererDX11::RendererRef;
    extern Effekseer::ManagerRef gManager;
    inline Effekseer::Matrix43 CnvMat43(DirectX::XMFLOAT4X4 mat)
    {
        Effekseer::Matrix43 mat43{};
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 3; ++j) {
                mat43.Value[i][j] = mat.m[i][j];
            }
        }
        return mat43;
    }


    inline Effekseer::Matrix44 CnvMat(DirectX::XMFLOAT4X4 mat)
    {
        Effekseer::Matrix44 out;

        out.Values[0][0] = mat._11;
        out.Values[1][0] = mat._12;
        out.Values[2][0] = mat._13;
        out.Values[3][0] = mat._14;
        out.Values[0][1] = mat._21;
        out.Values[1][1] = mat._22;
        out.Values[2][1] = mat._23;
        out.Values[3][1] = mat._24;
        out.Values[0][2] = mat._31;
        out.Values[1][2] = mat._32;
        out.Values[2][2] = mat._33;
        out.Values[3][2] = mat._34;
        out.Values[0][3] = mat._41;
        out.Values[1][3] = mat._42;
        out.Values[2][3] = mat._43;
        out.Values[3][3] = mat._44;
        return out;
    }
    inline DirectX::XMFLOAT4X4 GetProjMat(bool transpose)
    {
        //DirectX::XMMATRIX mat = DirectX::XMMatrixPerspectiveFovLH(Camera::DefCam.fov_,
        //    Camera::DefCam.aspect_,
        //    Camera::DefCam.near_, Camera::DefCam.far_);
        DirectX::XMMATRIX mat = Camera::GetProjectionMatrix();
        if (transpose)
            mat = DirectX::XMMatrixTranspose(mat);
        DirectX::XMFLOAT4X4 fmat;
        DirectX::XMStoreFloat4x4(&fmat, mat);
        return fmat;
    }
    inline DirectX::XMFLOAT4X4 GetViewMat(bool transpose)
    {
        //DirectX::XMMATRIX mat = DirectX::XMMatrixLookAtLH(
        //    Camera::DefCam.position_, Camera::DefCam.target_, Camera::DefCam.upvector_
        //);
        DirectX::XMMATRIX mat = Camera::GetViewMatrix();
        if (transpose)
            mat = DirectX::XMMatrixTranspose(mat);
        DirectX::XMFLOAT4X4 fmat;
        DirectX::XMStoreFloat4x4(&fmat, mat);
        return fmat;
    }

    inline void RendererInit(RendererRef renderer, ID3D11Device* dev, ID3D11DeviceContext* dc, int max_square) {
        renderer = EffekseerRendererDX11::Renderer::Create(dev, dc, max_square);
    }

    inline void ManagerInit(const RendererRef& renderer, int max_square) {
        gManager = Effekseer::Manager::Create(max_square);
        gManager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);

        gManager->SetSpriteRenderer(renderer->CreateSpriteRenderer());
        gManager->SetRibbonRenderer(renderer->CreateRibbonRenderer());
        gManager->SetRingRenderer(renderer->CreateRingRenderer());
        gManager->SetTrackRenderer(renderer->CreateTrackRenderer());
        gManager->SetModelRenderer(renderer->CreateModelRenderer());

        gManager->SetTextureLoader(renderer->CreateTextureLoader());
        gManager->SetModelLoader(renderer->CreateModelLoader());
        gManager->SetMaterialLoader(renderer->CreateMaterialLoader());
        gManager->SetCurveLoader(Effekseer::MakeRefPtr<Effekseer::CurveLoader>());
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
            if (fs::is_regular_file(m_filePath)) {
                fs::path filepath(m_filePath);
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

        const fs::path m_filePath;
        Effekseer::EffectRef m_effectRef;

    };

    struct EFKTransform {
        DirectX::XMFLOAT4X4 matrix;
        bool                        isLoop = false;
        float                       speed = 1.0f;
        int                         maxFrame = 0;
    };

    class EFKInstance
    {
    public:

        EFKInstance(const std::shared_ptr<EFKData>& effect_data)
            : m_spEffectData(effect_data)
        {}


        std::shared_ptr<const EFKData> GetEffectData() const noexcept {
            return m_spEffectData;
        }

        double                           elapsedTime = 0;
        Effekseer::Handle                handle = 0;
        std::shared_ptr<EFKTransform> effectTransform;

    private:
        const std::shared_ptr<EFKData> m_spEffectData;

    };



    class EffekseerManager
    {
    public:

        virtual ~EffekseerManager() noexcept {
            Release();
        }

        void Initialize(ID3D11Device* dev, ID3D11DeviceContext* dc, int max_square = 8192) {
            RendererInit(m_rendererRef, dev, dc, max_square);
            ManagerInit(m_rendererRef, max_square);
        }

        void Update(double delta_time) {
            constexpr double effect_frame{ DEFAULT_FRAME_RATE };
            for (auto iter = m_upEffectInstances.begin(); iter != m_upEffectInstances.end();) 
            {
                auto& data = *iter->second;
                auto& handle = iter->second->handle;
                auto& tranform = iter->second->effectTransform;

                if (data.elapsedTime == 0) {
                    handle = m_managerRef->Play(data.GetEffectData()->GetEffectRef(), 0, 0, 0);
                }

                if (data.elapsedTime > (tranform->maxFrame / effect_frame)) {
                    m_managerRef->StopEffect(handle);
                    if (tranform->isLoop) {
                        data.elapsedTime = 0;
                    }
                    else {
                        iter = m_upEffectInstances.erase(iter);
                    }
                }
                else {
                    m_rendererRef->SetTime(static_cast<float>(data.elapsedTime));
                    m_managerRef->SetMatrix(handle, CnvMat43(tranform->matrix));
                    m_managerRef->SetSpeed(handle, tranform->speed);
                    data.elapsedTime += delta_time;
                    ++iter;
                }
            }

            m_managerRef->Update(static_cast<float>(delta_time * effect_frame));
        }

        void Draw() {
            m_rendererRef->BeginRendering();
            m_managerRef->Draw();
            m_rendererRef->EndRendering();
        }

        void SetCamera(const Effekseer::Matrix44 proj_mat, const Effekseer::Matrix44& view_mat) {
            m_rendererRef->SetProjectionMatrix(CnvMat(GetProjMat(true)));
            m_rendererRef->SetCameraMatrix(CnvMat(GetViewMat(true)));
        }

        void SetEffect(std::string_view effect_name, std::string_view file_path) {
            m_spEffectData.emplace(effect_name, std::make_shared<EFKData>(m_managerRef, file_path));
        }

        std::shared_ptr<EFKTransform> Play(std::string_view effect_name, const EFKTransform& effect_transform, bool is_unique = false) {
            if (is_unique) {
                if (auto iter = m_upEffectInstances.find(effect_name.data()); iter != m_upEffectInstances.end()) {
                    return iter->second->effectTransform;
                }
            }
            if (auto iter = m_spEffectData.find(effect_name.data()); iter != m_spEffectData.end()) {
                auto effect_instance = std::make_unique<EFKInstance>(iter->second);
                effect_instance->effectTransform = std::make_shared<EFKTransform>(effect_transform);
                auto& sp_et = effect_instance->effectTransform;
                m_upEffectInstances.emplace(effect_name, std::move(effect_instance));
                return sp_et;
            }
            else {
                assert::ShowError(ASSERT_FILE_LINE, "EffectData is not found.");
            }
            return nullptr;
        }
        void SetFPS(float fps) { fps_ = fps; }

    private:

        void Release() noexcept {
            m_managerRef.Reset();
            m_rendererRef.Reset();
        }

        float fps_;
        RendererRef                                                        m_rendererRef;
        Effekseer::ManagerRef                                              m_managerRef;
        std::unordered_map<std::string, std::shared_ptr<EFKData>>          m_spEffectData;
        std::unordered_multimap<std::string, std::unique_ptr<EFKInstance>> m_upEffectInstances;

    };

}