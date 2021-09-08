//#include "CameraSystem.h"
//#include "ECSFactory.h"
//#include "CameraComponent.h"
//
//
//DirectX::XMFLOAT3 CameraSystem::GetPosition(const std::string& camName) const
//{
//    auto view = ECSFactory::GetComponents<CameraComponent>();
//    for (auto e : view)
//    {
//        auto& cam = view.get<CameraComponent>(e);
//
//        if (cam.m_Name == camName)
//        {
//            return cam.m_CamPos;
//        }
//
//        
//    }
//   
//}
//
//void CameraSystem::DrawImgui()
//{
//    auto view = ECSFactory::GetComponents<CameraComponent,MainCamera>();
//    for (auto e : view)
//    {
//        auto& cam = view.get<CameraComponent>(e);
//
//        cam.DrawImgui();
//
//
//    }
//}
//
//void CameraSystem::UpdateViewXM(float dt)
//{
//    //auto view = ECSFactory::GetComponents<CameraComponent>();
//
//    //for (auto e : view)
//    //{
//    //    auto& cam = view.get<CameraComponent>(e);
//    //    cam.UpdateXM(dt);
//    //}
//
//}
