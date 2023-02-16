#include "command_recorder.h"

#include <toy_renderer/graphics_api.h>
#include <toy_renderer/api/api_command_recorder.h>

namespace ToyRenderer {

CommandRecorder::CommandRecorder(GraphicsApi *api, const Handle<Device_t> &device, const Handle<CommandRecorder_t> &commandRecorder)
    : m_api(api)
    , m_device(device)
    , m_commandRecorder(commandRecorder)
{
}

CommandRecorder::~CommandRecorder()
{
}

RenderPassCommandRecorder CommandRecorder::beginRenderPass(const RenderPassOptions &options)
{
    return RenderPassCommandRecorder(m_api, m_device, m_api->resourceManager()->createRenderPassCommandRecorder(m_device, options));
}

CommandBuffer CommandRecorder::finish()
{
    auto apiCommandRecorder = m_api->resourceManager()->getCommandRecorder(m_commandRecorder);
    return CommandBuffer(apiCommandRecorder->finish());
}

} // namespace ToyRenderer
