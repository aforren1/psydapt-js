#include <emscripten.h>
#include <emscripten/bind.h>
#include <array>

#include "psydapt/questplus/csf.hpp"
#include "../helper.hpp"

namespace em = emscripten;
using psydapt::questplus::CSF;

namespace questplus
{
    class EmCSF : public CSF
    {
    private:
        CSF::Params sanitize(em::val params)
        {
            CSF::Params p;
            // base params for all quest+
            convert(p.stim_selection_method, params["stim_selection_method"]);
            convert(p.param_estimation_method, params["param_estimation_method"]);
            convert(p.n, params["n"]);
            convert(p.max_consecutive_reps, params["max_consecutive_reps"]);
            convert(p.random_seed, params["random_seed"]);
            // begin CSF-specific
            convert(p.stim_scale, params["stim_scale"]);
            // stimuli
            convert(p.contrast, params["contrast"]);
            convert(p.spatial_freq, params["spatial_freq"]);
            convert(p.temporal_freq, params["temporal_freq"]);
            // parameters
            convert(p.c0, params["c0"]);
            convert(p.cf, params["cf"]);
            convert(p.cw, params["cw"]);
            convert(p.min_thresh, params["min_thresh"]);
            convert(p.slope, params["slope"]);
            convert(p.lower_asymptote, params["lower_asymptote"]);
            convert(p.lapse_rate, params["lapse_rate"]);
            // priors
            convert(p.c0_prior, params["c0_prior"]);
            convert(p.cf_prior, params["cf_prior"]);
            convert(p.cw_prior, params["cw_prior"]);
            convert(p.min_thresh_prior, params["min_thresh_prior"]);
            convert(p.slope_prior, params["slope_prior"]);
            convert(p.lower_asymptote_prior, params["lower_asymptote_prior"]);
            convert(p.lapse_rate_prior, params["lapse_rate_prior"]);
            return p;
        }

    public:
        EmCSF(em::val params) : CSF::CSF(sanitize(params)) {}
        bool update(int response)
        {
            return CSF::update(response);
        }
        bool update2(int response, em::val stimulus)
        {
            std::array<double, 3> stim;
            const size_t l = stimulus["length"].as<size_t>();
            if (l != 3)
            {
                PSYDAPT_THROW(std::invalid_argument, "Update stimuli must be of length 3.");
            }
            em::val memoryView{em::typed_memory_view(l, stim.data())};
            memoryView.call<void>("set", stimulus);
            return CSF::update(response, stim);
        }

        em::val next2()
        {
            std::array<double, 3> stim = CSF::next();
            return em::val::array(stim.begin(), stim.end());
        }
    };

} // namespace questplus