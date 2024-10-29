/*
 * Copyright (c) 2020, Matthew Olsson <mattco@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/DOM/Document.h>
#include <LibWeb/DOM/Element.h>
#include <LibWeb/HTML/HTMLOrSVGElement.h>
#include <LibWeb/SVG/SVGAnimatedString.h>

namespace Web::SVG {

class SVGElement
    : public DOM::Element
    , public HTML::GlobalEventHandlers
    , public HTML::HTMLOrSVGElement<SVGElement> {
    WEB_PLATFORM_OBJECT(SVGElement, DOM::Element);

public:
    virtual bool requires_svg_container() const override { return true; }

    JS::NonnullGCPtr<SVGAnimatedString> class_name();
    JS::GCPtr<SVGSVGElement> owner_svg_element();

protected:
    SVGElement(DOM::Document&, DOM::QualifiedName);

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;

    virtual void attribute_changed(FlyString const& name, Optional<String> const& old_value, Optional<String> const& value) override;
    virtual void attribute_change_steps(FlyString const&, Optional<String> const&, Optional<String> const&, Optional<FlyString> const&) override;
    virtual WebIDL::ExceptionOr<void> cloned(DOM::Node&, bool) override;
    virtual void children_changed() override;
    virtual void inserted() override;
    virtual void removed_from(Node*) override;

    void update_use_elements_that_reference_this();
    void remove_from_use_element_that_reference_this();

    JS::NonnullGCPtr<SVGAnimatedLength> svg_animated_length_for_property(CSS::PropertyID) const;

private:
    // ^HTML::GlobalEventHandlers
    virtual JS::GCPtr<DOM::EventTarget> global_event_handlers_to_event_target(FlyString const&) override { return *this; }

    virtual bool is_svg_element() const final { return true; }

    JS::GCPtr<SVGAnimatedString> m_class_name_animated_string;
};

}

namespace Web::DOM {

template<>
inline bool Node::fast_is<SVG::SVGElement>() const { return is_svg_element(); }

}
