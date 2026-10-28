#pragma once
#include "Config.h"
#include "QueueFamilies.hpp"

namespace vkl{
    struct GraphicsContext{
        enum Type{
            eCompute,
            eGraphics,
            ePresent,
            eTransfer
        };

        vk::Device device;
        vk::PhysicalDevice physical_device;
        
        //family queue
        vkl::Queue graphics_queue;
        vkl::Queue present_queue;
        vkl::Queue transfer_queue;
        vkl::Queue compute_queue;

        vk::CommandPool graph_pres_command_pool;
        vk::CommandPool transfer_command_pool;
        vk::CommandPool compute_command_pool;

        vk::CommandBuffer graph_pres_command_buffer;
        vk::CommandBuffer transfer_command_buffer;
        vk::CommandBuffer compute_command_buffer;

        vk::DescriptorPool descriptor_pool;
        auto get_command_pool(Type type){
            switch (type){
                case Type::eCompute:
                    return compute_command_pool;
                case Type::eGraphics:
                case Type::ePresent:
                    return graph_pres_command_pool;
                case Type::eTransfer:
                    return transfer_command_pool;
                default:
                    std::unreachable();
            }
            std::unreachable();
        }
        auto get_command_buffer(Type type){
            switch (type){
                case Type::eCompute:
                    return compute_command_buffer;
                case Type::eGraphics:
                case Type::ePresent:
                    return graph_pres_command_buffer;
                case Type::eTransfer:
                    return transfer_command_buffer;
                default:
                    std::unreachable();
            }
            std::unreachable();
        }
        auto get_queue(Type type){
            switch (type){
                case Type::eCompute:
                    return compute_queue;
                case Type::eGraphics:
                    return graphics_queue;
                case Type::ePresent:
                    return present_queue;
                case Type::eTransfer:
                    return transfer_queue;
                default:
                    std::unreachable();
            }
            std::unreachable();
        }
    };

}