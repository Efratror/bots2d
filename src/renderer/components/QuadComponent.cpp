#include "components/Transforms.h"
#include "renderer/components/QuadComponent.h"
#include "renderer/Renderer.h"

QuadComponent::QuadComponent(const QuadTransform *transform, const glm::vec4 &color) :
    m_transform(transform),
    m_color(color)
{
    assert(transform != nullptr);
}

QuadComponent::~QuadComponent()
{
}

void QuadComponent::onFixedUpdate()
{
    if (m_enabled == false) {
        return;
    }

    Renderer::drawQuad(m_transform->quadCoords, m_color);
}
