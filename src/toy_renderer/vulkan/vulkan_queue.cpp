#include "vulkan_queue.h"

#include <toy_renderer/queue.h>
#include <toy_renderer/vulkan/vulkan_resource_manager.h>

namespace ToyRenderer {

VulkanQueue::VulkanQueue(VkQueue _queue,
                         VulkanResourceManager *_vulkanResourceManager)
    : ApiQueue()
    , queue(_queue)
    , vulkanResourceManager(_vulkanResourceManager)
{
}

void VulkanQueue::submit(const SubmitOptions &options)
{
    // TODO: Do we need to expose the wait stage flags to the public API or is waiting
    // for the semaphores at the top of the pipeline good enough?
    const uint32_t waitSemaphoreCount = static_cast<uint32_t>(options.waitSemaphores.size());
    std::vector<VkSemaphore> vkWaitSemaphores;
    std::vector<VkPipelineStageFlags> vkWaitStageFlags;
    vkWaitSemaphores.reserve(waitSemaphoreCount);
    vkWaitStageFlags.reserve(waitSemaphoreCount);
    for (uint32_t i = 0; i < waitSemaphoreCount; ++i) {
        auto vulkanSemaphore = vulkanResourceManager->getGpuSemaphore(options.waitSemaphores.at(i));
        if (vulkanSemaphore) {
            vkWaitSemaphores.push_back(vulkanSemaphore->semaphore);
            vkWaitStageFlags.push_back(VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT);
        }
    }

    const uint32_t signalSemaphoreCount = static_cast<uint32_t>(options.signalSemaphores.size());
    std::vector<VkSemaphore> vkSignalSemaphores;
    vkSignalSemaphores.reserve(signalSemaphoreCount);
    for (uint32_t i = 0; i < signalSemaphoreCount; ++i) {
        auto vulkanSemaphore = vulkanResourceManager->getGpuSemaphore(options.signalSemaphores.at(i));
        if (vulkanSemaphore)
            vkSignalSemaphores.push_back(vulkanSemaphore->semaphore);
    }

    const uint32_t commandBufferCount = static_cast<uint32_t>(options.commandBuffers.size());
    std::vector<VkCommandBuffer> vkCommandBuffers;
    vkCommandBuffers.reserve(commandBufferCount);
    for (uint32_t i = 0; i < commandBufferCount; ++i) {
        auto vulkanCommandBuffer = vulkanResourceManager->getCommandBuffer(options.commandBuffers.at(i));
        if (vulkanCommandBuffer)
            vkCommandBuffers.push_back(vulkanCommandBuffer->commandBuffer);
    }

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = static_cast<uint32_t>(vkWaitSemaphores.size());
    submitInfo.pWaitSemaphores = vkWaitSemaphores.data();
    submitInfo.pWaitDstStageMask = vkWaitStageFlags.data();

    submitInfo.signalSemaphoreCount = static_cast<uint32_t>(vkSignalSemaphores.size());
    submitInfo.pSignalSemaphores = vkSignalSemaphores.data();

    submitInfo.commandBufferCount = static_cast<uint32_t>(vkCommandBuffers.size());
    submitInfo.pCommandBuffers = vkCommandBuffers.data();

    // TODO: Support fences
    // Make sure the fence is ready for use and submit
    // VkFence inFlightFences[] = { frameFence };
    // vkResetFences(renderer()->vulkanDevice()->device(), 1, inFlightFences);

    VkResult result = vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
}

void VulkanQueue::present(const PresentOptions &options)
{
    const uint32_t waitSemaphoreCount = static_cast<uint32_t>(options.waitSemaphores.size());
    std::vector<VkSemaphore> vkWaitSemaphores;
    vkWaitSemaphores.reserve(waitSemaphoreCount);
    for (uint32_t i = 0; i < waitSemaphoreCount; ++i) {
        auto vulkanSemaphore = vulkanResourceManager->getGpuSemaphore(options.waitSemaphores.at(i));
        if (vulkanSemaphore)
            vkWaitSemaphores.push_back(vulkanSemaphore->semaphore);
    }

    const uint32_t swapchainCount = static_cast<uint32_t>(options.swapchainInfos.size());
    std::vector<VkSwapchainKHR> vkSwapchains;
    std::vector<uint32_t> imageIndices;
    vkSwapchains.reserve(swapchainCount);
    imageIndices.reserve(swapchainCount);
    for (uint32_t i = 0; i < swapchainCount; ++i) {
        auto vulkanSwapchain = vulkanResourceManager->getSwapchain(options.swapchainInfos.at(i).swapchain);
        if (vulkanSwapchain) {
            vkSwapchains.push_back(vulkanSwapchain->swapchain);
            imageIndices.push_back(options.swapchainInfos.at(i).imageIndex);
        }
    }
    std::vector<VkResult> presentResults(vkSwapchains.size());

    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = static_cast<uint32_t>(vkWaitSemaphores.size());
    presentInfo.pWaitSemaphores = vkWaitSemaphores.data();
    presentInfo.swapchainCount = static_cast<uint32_t>(vkSwapchains.size());
    presentInfo.pSwapchains = vkSwapchains.data();
    presentInfo.pImageIndices = imageIndices.data();
    presentInfo.pResults = presentResults.data();

    const VkResult result = vkQueuePresentKHR(queue, &presentInfo);

    // TODO: Map the return code to something api agnostic
}

} // namespace ToyRenderer
