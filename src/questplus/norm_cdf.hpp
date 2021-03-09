#include <emscripten.h>
#include <emscripten/bind.h>

#include "psydapt/questplus/norm_cdf.hpp"
#include "../helper.hpp"

namespace em = emscripten;
using psydapt::questplus::NormCDF;

namespace questplus
{
    class EmNormCDF : public NormCDF
    {
    private:
        NormCDF::Params sanitize(em::val params)
        {
            NormCDF::Params p;
            // base params for all quest+
            convert(p.stim_selection_method, params["stim_selection_method"]);
            convert(p.param_estimation_method, params["param_estimation_method"]);
            convert(p.n, params["n"]);
            convert(p.max_consecutive_reps, params["max_consecutive_reps"]);
            convert(p.random_seed, params["random_seed"]);
            // end of base params
            // begin NormCDF-specific
            convert(p.stim_scale, params["stim_scale"]);

            convert(p.intensity, params["intensity"]);
            convert(p.location, params["location"]);
            convert(p.scale, params["scale"]);
            convert(p.lower_asymptote, params["lower_asymptote"]);
            convert(p.lapse_rate, params["lapse_rate"]);
            // priors
            convert(p.location_prior, params["location_prior"]);
            convert(p.scale_prior, params["scale_prior"]);
            convert(p.lower_asymptote_prior, params["lower_asymptote_prior"]);
            convert(p.lapse_rate_prior, params["lapse_rate_prior"]);
            return p;
        }

    public:
        EmNormCDF(em::val params) : NormCDF::NormCDF(sanitize(params)) {}
        bool update(int response)
        {
            return NormCDF::update(response);
        }
        bool update(int response, double stimulus)
        {
            return NormCDF::update(response, stimulus);
        }

        double next()
        {
            return NormCDF::next();
        }
    };
} // namespace questplus
