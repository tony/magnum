/*
    This file is part of Magnum.

    Copyright © 2010, 2011, 2012, 2013, 2014, 2015, 2016
              Vladimír Vondruš <mosra@centrum.cz>

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
*/

#include <sstream>
#include <Corrade/TestSuite/Tester.h>

#include "Magnum/Magnum.h"
#include "Magnum/Audio/Context.h"
#include "Magnum/Audio/Renderer.h"

namespace Magnum { namespace Audio { namespace Test {

struct RendererTest: TestSuite::Tester {
    explicit RendererTest();
    void listenerOrientation();
    void listenerPosition();
    void listenerVelocity();
    void listenerGain();
    void speedOfSound();
    void dopplerFactor();
    void distanceModel();

    void debugError();
    void debugDistanceModel();

    Context _context;
};

RendererTest::RendererTest() {
    addTests({&RendererTest::listenerOrientation,
              &RendererTest::listenerPosition,
              &RendererTest::listenerVelocity,
              &RendererTest::listenerGain,
              &RendererTest::speedOfSound,
              &RendererTest::dopplerFactor,
              &RendererTest::distanceModel,

              &RendererTest::debugError,
              &RendererTest::debugDistanceModel});
}

void RendererTest::listenerOrientation() {
    constexpr Vector3 up{1.0f, 2.0f, 3.0f}, fwd{3.0f, 2.0f, 1.0f};
    Renderer::setListenerOrientation(fwd, up);
    std::array<Vector3, 2> orientation = Renderer::listenerOrientation();

    CORRADE_COMPARE(orientation[0], fwd);
    CORRADE_COMPARE(orientation[1], up);
}

void RendererTest::listenerPosition() {
    constexpr Vector3 pos{1.0f, 3.0f, 2.0f};
    Renderer::setListenerPosition(pos);

    CORRADE_COMPARE(Renderer::listenerPosition(), pos);
}

void RendererTest::listenerVelocity() {
    constexpr Vector3 vel{1.0f, 3.0f, 2.0f};
    Renderer::setListenerVelocity(vel);

    CORRADE_COMPARE(Renderer::listenerVelocity(), vel);
}

void RendererTest::listenerGain() {
    constexpr Float gain = 0.512f;
    Renderer::setListenerGain(gain);

    CORRADE_COMPARE(Renderer::listenerGain(), gain);
}

void RendererTest::speedOfSound() {
    constexpr Float speed = 1.25f;
    Renderer::setSpeedOfSound(speed);

    CORRADE_COMPARE(Renderer::speedOfSound(), speed);
}

void RendererTest::dopplerFactor() {
    constexpr Float factor = 0.3335f;
    Renderer::setDopplerFactor(factor);

    CORRADE_COMPARE(Renderer::dopplerFactor(), factor);
}

void RendererTest::distanceModel() {
    constexpr Renderer::DistanceModel model = Renderer::DistanceModel::InverseClamped;
    Renderer::setDistanceModel(model);

    CORRADE_COMPARE(Renderer::distanceModel(), model);
}

void RendererTest::debugError() {
    std::ostringstream out;
    Debug(&out) << Renderer::Error::InvalidOperation << Renderer::Error(0xdead);
    CORRADE_COMPARE(out.str(), "Audio::Renderer::Error::InvalidOperation Audio::Renderer::Error(0xdead)\n");
}

void RendererTest::debugDistanceModel() {
    std::ostringstream out;
    Debug(&out) << Renderer::DistanceModel::Inverse << Renderer::DistanceModel(0xdead);
    CORRADE_COMPARE(out.str(), "Audio::Renderer::DistanceModel::Inverse Audio::Renderer::DistanceModel(0xdead)\n");
}

}}}

CORRADE_TEST_MAIN(Magnum::Audio::Test::RendererTest)
