/*
  This file is part of KDXr.

  SPDX-FileCopyrightText: 2023 Klarälvdalens Datakonsult AB, a KDAB Group company <info@kdab.com>

  SPDX-License-Identifier: MIT

  Contact KDAB at <info@kdab.com> for commercial licensing options.
*/

#include "instance.h"

#include <KDXr/xr_api.h>
#include <KDXr/api/resource_manager_impl.h>

#include <KDXr/utils/logging.h>

namespace KDXr {

/**
    @class Instance
    @brief Instance is used to initialize the XR API.
    @ingroup public
    @headerfile instance.h <KDXr/instance.h>

    @code{.cpp}
    using namespace KDXr;

    std::unique_ptr<XrApi> api = std::make_unique<OpenXrApi>();

    Instance instance = api->createInstance(InstanceOptions{
            .applicationName = "MyApplication",
            .applicationVersion = 0,
    });
    @endcode

    @sa InstanceOptions
    @sa XrApi::createInstance
 */

/**
    @fn Instance::handle()
    @brief Returns the handle used to retrieve the underlying Rendering API specific Instance

    @return KDGpu::Handle<Instance_t>
    @sa ResourceManager
 */

/**
    @fn Instance::isValid()
    @brief Convenience function to check whether the Instance is actually referencing a valid API specific resource
 */

Instance::Instance()
{
}

Instance::Instance(XrApi *api, const InstanceOptions &options)
{
    // Create an instance using the underlying API
    m_api = api;
    m_instance = m_api->resourceManager()->createInstance(options);
    auto apiInstance = m_api->resourceManager()->getInstance(m_instance);
    apiInstance->initialize(this);
}

Instance::~Instance()
{
    if (isValid())
        m_api->resourceManager()->deleteInstance(handle());
}

Instance::Instance(Instance &&other)
{
    m_api = std::exchange(other.m_api, nullptr);
    m_instance = std::exchange(other.m_instance, {});

    if (m_api && m_instance.isValid()) {
        auto apiInstance = m_api->resourceManager()->getInstance(m_instance);
        apiInstance->initialize(this);
    }
}

Instance &Instance::operator=(Instance &&other)
{
    if (this != &other) {
        if (isValid())
            m_api->resourceManager()->deleteInstance(handle());

        m_api = std::exchange(other.m_api, nullptr);
        m_instance = std::exchange(other.m_instance, {});

        if (m_api && m_instance.isValid()) {
            auto apiInstance = m_api->resourceManager()->getInstance(m_instance);
            apiInstance->initialize(this);
        }
    }
    return *this;
}

/**
 * @brief Returns the extensions requested for the instance
 */
std::vector<ApiLayer> Instance::enabledApiLayers() const
{
    auto apiInstance = m_api->resourceManager()->getInstance(m_instance);
    return apiInstance->enabledApiLayers();
}

std::vector<Extension> Instance::enabledExtensions() const
{
    auto apiInstance = m_api->resourceManager()->getInstance(m_instance);
    return apiInstance->enabledExtensions();
}

InstanceProperties Instance::properties() const
{
    auto apiInstance = m_api->resourceManager()->getInstance(m_instance);
    return apiInstance->properties();
}

System *Instance::system(const SystemOptions &options)
{
    if (!m_system.isValid()) {
        auto apiInstance = m_api->resourceManager()->getInstance(m_instance);
        auto systemHandle = apiInstance->querySystem(options, m_instance);
        if (!systemHandle.isValid()) {
            return nullptr;
        }
        m_system = std::move(System(m_api, systemHandle));
    }

    return &m_system;
}

ProcessEventsResult Instance::processEvents()
{
    auto apiInstance = m_api->resourceManager()->getInstance(m_instance);
    return apiInstance->processEvents();
}

ActionSet Instance::createActionSet(const ActionSetOptions &options)
{
    return ActionSet(m_api, m_instance, options);
}

SuggestActionBindingsResult Instance::suggestActionBindings(const SuggestActionBindingsOptions &options)
{
    auto apiInstance = m_api->resourceManager()->getInstance(m_instance);
    return apiInstance->suggestActionBindings(options);
}

} // namespace KDXr
