/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/ARIA/Roles.h>
#include <LibWeb/HTML/HTMLElement.h>
#include <LibWeb/HTML/WindowEventHandlers.h>

namespace Web::HTML {

class HTMLBodyElement final
    : public HTMLElement
    , public WindowEventHandlers {
    WEB_PLATFORM_OBJECT(HTMLBodyElement, HTMLElement);

public:
    virtual ~HTMLBodyElement() override;

    virtual void parse_attribute(DeprecatedFlyString const&, DeprecatedString const&) override;
    virtual void apply_presentational_hints(CSS::StyleProperties&) const override;

    // https://www.w3.org/TR/html-aria/#el-body
    virtual Optional<ARIA::Role> default_role() const override { return ARIA::Role::generic; };

private:
    HTMLBodyElement(DOM::Document&, DOM::QualifiedName);

    virtual JS::ThrowCompletionOr<void> initialize(JS::Realm&) override;

    // ^HTML::GlobalEventHandlers
    virtual EventTarget& global_event_handlers_to_event_target(DeprecatedFlyString const& event_name) override;

    // ^HTML::WindowEventHandlers
    virtual EventTarget& window_event_handlers_to_event_target() override;

    RefPtr<CSS::ImageStyleValue> m_background_style_value;
};

}
