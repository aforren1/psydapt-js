#include <string>
#include <emscripten/bind.h>
#include <optional>

#include "psydapt.hpp"

namespace em = emscripten;
using psydapt::staircase::Staircase;

// TODO: how to error early when arguments are not provided?
class EmStaircase : public Staircase
{
private:
    Staircase::Params sanitize(em::val params)
    {
        Staircase::Params p;

        em::val start_val = params["start_val"];
        if (start_val.isNumber())
        {
            p.start_val = start_val.as<double>();
        }

        em::val n_reversals = params["n_reversals"];
        if (n_reversals.isNumber())
        {
            p.n_reversals = n_reversals.as<unsigned int>();
        }
        em::val step_sizes = params["step_sizes"];
        if (step_sizes.isArray())
        {
            p.step_sizes = em::convertJSArrayToNumberVector<double>(step_sizes);
        }
        em::val n_trials = params["n_trials"];
        if (n_trials.isNumber())
        {
            p.n_trials = n_trials.as<unsigned int>();
        }
        em::val n_up = params["n_up"];
        if (n_up.isNumber())
        {
            p.n_up = n_up.as<int>();
        }

        em::val n_down = params["n_down"];
        if (n_down.isNumber())
        {
            p.n_down = n_down.as<int>();
        }
        em::val apply_initial_rule = params["apply_initial_rule"];
        if (apply_initial_rule.typeOf().as<std::string>() == "boolean")
        {
            p.apply_initial_rule = apply_initial_rule.as<bool>();
        }

        em::val stim_scale = params["stim_scale"];
        if (stim_scale.isString())
        {
            std::string stim_str = stim_scale.as<std::string>();
            psydapt::Scale s;
            if (stim_str == "Linear")
            {
                s = psydapt::Scale::Linear;
            }
            else if (stim_str == "dB")
            {
                s = psydapt::Scale::dB;
            }
            else if (stim_str == "Log10")
            {
                s = psydapt::Scale::Log10;
            }
            else
            {
                // TODO: error
                s = psydapt::Scale::Linear;
            }
            p.stim_scale = s;
        }

        em::val min_val = params["min_val"];
        if (min_val.isNumber())
        {
            p.min_val = min_val.as<double>();
        }

        em::val max_val = params["max_val"];
        if (max_val.isNumber())
        {
            p.max_val = max_val.as<double>();
        }

        return p;
    }

public:
    EmStaircase(em::val params) : Staircase::Staircase(sanitize(params)) {}

    bool update(int value)
    {
        return Staircase::update(value);
    }
    bool update(int value, double stimulus)
    {
        return Staircase::update(value, stimulus);
    }

    double next()
    {
        return Staircase::next();
    }
};
