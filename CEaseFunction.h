#pragma once
#include <cmath>
#include <DirectXMath.h>
#include <map>
#include <string>
#include <functional>

using namespace DirectX;

class CEaseFunction
{
    std::map<std::string, std::function<double(double)>> FUNC
    {
        {"easeInSine",    [](double t) { return (sin(XM_PIDIV2 * t));        }},
        {"easeOutSine",   [](double t) { return (1 + sin(XM_PIDIV2 * (--t))); }},
        {"easeInOutSine", [](double t) {  return 0.5 * (1 + sin(XM_PI * (t - 0.5))); }},
        {"easeInQuad",    [](double t) {  return t * t; }},
        {"easeOutQuad",    [](double t) { return t * (2 - t); }},
        {"easeInOutQuad",   [](double t) { return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1; }},
        {"easeInCubic",     [](double t) { return t * t * t; }},
        {"easeOutCubic",    [](double t) { return 1 + (--t) * t * t; }},
        {"easeInOutCubic",  [](double t) { return t < 0.5 ? 4 * t * t * t : 1 + (--t) * (2 * (--t)) * (2 * t); }},
        {"easeInQuart",     [](double t) {   t *= t; return t * t; }},
        {"easeOutQuart",    [](double t) {   t = (--t) * t; return 1 - t * t; }},
        {"easeInOutQuart",  [](double t) { if (t < 0.5) {
                                                t *= t; return 8 * t * t;
                                             }
else {
  t = (--t) * t;
  return 1 - 8 * t * t;
} }},
{"easeInQuint",    [](double t) { double t2 = t * t; return t * t2 * t2; },
{"easeInOutQuint",     [](double t) { double t2;
                                      if (t < 0.5) {
                                          t2 = t * t;
                                          return 16 * t * t2 * t2;
                                      }
                                      else {
                                          t2 = (--t) * t;
                                          return 1 + 16 * t * t2 * t2;
}},
{"easeInExpo",    [](double t) { return (pow(2, 8 * t) - 1) / 255; }},
{"easeOutExpo",    [](double t) { return 1 - pow(2, -8 * t); }},
{"easeInOutExpo",    [](double t) {if (t < 0.5) {
                                        return (pow(2, 16 * t) - 1) / 510;
                                    }
                                    else {
                                        return 1 - 0.5 * pow(2, -16 * (t - 0.5));} }},
{"easeInCirc",    [](double t) { return 1 - sqrt(1 - t); }},



        double easeOutCirc(double t) {
            return sqrt(t);
        }

        double easeInOutCirc(double t) {
            if (t < 0.5) {
                return (1 - sqrt(1 - 2 * t)) * 0.5;
            }
            else {
                return (1 + sqrt(2 * t - 1)) * 0.5;
            }
        }

        double easeInBack(double t) {
            return t * t * (2.70158 * t - 1.70158);
        }

        double easeOutBack(double t) {
            return 1 + (--t) * t * (2.70158 * t + 1.70158);
        }

        double easeInOutBack(double t) {
            if (t < 0.5) {
                return t * t * (7 * t - 2.5) * 2;
            }
            else {
                return 1 + (--t) * t * 2 * (7 * t + 2.5);
            }
        }

        double easeInElastic(double t) {
            double t2 = t * t;
            return t2 * t2 * sin(t * XM_PI * 4.5);
        }

        double easeOutElastic(double t) {
            double t2 = (t - 1) * (t - 1);
            return 1 - t2 * t2 * cos(t * XM_PI * 4.5);
        }

        double easeInOutElastic(double t) {
            double t2;
            if (t < 0.45) {
                t2 = t * t;
                return 8 * t2 * t2 * sin(t * XM_PI * 9);
            }
            else if (t < 0.55) {
                return 0.5 + 0.75 * sin(t * XM_PI * 4);
            }
            else {
                t2 = (t - 1) * (t - 1);
                return 1 - 8 * t2 * t2 * sin(t * XM_PI * 9);
            }
        }

        double easeInBounce(double t) {
            return pow(2, 6 * (t - 1)) * abs(sin(t * XM_PI * 3.5));
        }

        double easeOutBounce(double t) {
            return 1 - pow(2, -6 * t) * abs(cos(t * XM_PI * 3.5));
        }

        double easeInOutBounce(double t) {
            if (t < 0.5) {
                return 8 * pow(2, 8 * (t - 1)) * abs(sin(t * XM_PI * 7));
            }
            else {
                return 1 - 8 * pow(2, -8 * t) * abs(sin(t * XM_PI * 7));
            }
        }
    };

};

