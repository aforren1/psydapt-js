#include <emscripten/bind.h>

#include "psydapt/questplus/weibull.hpp"
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
            auto temp = params["min_n_entropy_params"];
            if (temp.typeOf().as<std::string>() == "object")
            {
                convert(p.min_n_entropy_params.n, temp["n"]);
                convert(p.min_n_entropy_params.max_consecutive_reps, temp["max_consecutive_reps"]);
                convert(p.min_n_entropy_params.random_seed, temp["random_seed"]);
            }
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
