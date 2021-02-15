#include <string>
#include <emscripten/bind.h>
#include <optional>

#include "psydapt.hpp"
#include "helper.hpp"

namespace em = emscripten;
using psydapt::staircase::Staircase;

// TODO: how to error early when arguments are not provided?
class EmStaircase : public Staircase
{
private:
    Staircase::Params sanitize(em::val params)
    {
        Staircase::Params p;

        convert(p.start_val, params["start_val"]);
        convert(p.n_reversals, params["n_reversals"]);
        convert(p.step_sizes, params["step_sizes"]);
        convert(p.n_trials, params["n_trials"]);
        convert(p.n_up, params["n_up"]);
        convert(p.n_down, params["n_down"]);
        convert(p.apply_initial_rule, params["apply_initial_rule"]);
        convert(p.stim_scale, params["stim_scale"]["value"]);
        convert(p.min_val, params["min_val"]);
        convert(p.max_val, params["max_val"]);

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
