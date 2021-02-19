#include <emscripten/bind.h>

#include "psydapt.hpp"
#include "../helper.hpp"

namespace em = emscripten;
using psydapt::questplus::Weibull;

namespace questplus
{
    class EmWeibull : public Weibull
    {
    private:
        Weibull::Params sanitize(em::val params)
        {
            Weibull::Params p;
            // base params for all quest+
            convert(p.stim_selection_method, params["stim_selection_method"]);
            convert(p.param_estimation_method, params["param_estimation_method"]);
            convert(p.n, params["n"]);
            convert(p.max_consecutive_reps, params["max_consecutive_reps"]);
            convert(p.random_seed, params["random_seed"]);
            // end of base params
            // begin Weibull-specific
            convert(p.stim_scale, params["stim_scale"]);

            convert(p.intensity, params["intensity"]);
            convert(p.threshold, params["threshold"]);
            convert(p.slope, params["slope"]);
            convert(p.lower_asymptote, params["lower_asymptote"]);
            convert(p.lapse_rate, params["lapse_rate"]);
            // priors
            convert(p.threshold_prior, params["threshold_prior"]);
            convert(p.slope_prior, params["slope_prior"]);
            convert(p.lower_asymptote_prior, params["lower_asymptote_prior"]);
            convert(p.lapse_rate_prior, params["lapse_rate_prior"]);
            return p;
        }

    public:
        EmWeibull(em::val params) : Weibull::Weibull(sanitize(params)) {}
        bool update(int response)
        {
            return Weibull::update(response);
        }
        bool update(int response, double stimulus)
        {
            return Weibull::update(response, stimulus);
        }

        double next()
        {
            return Weibull::next();
        }
    };
} // namespace questplus
