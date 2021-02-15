#include <string>
#include <optional>

#include <emscripten.h>
#include <emscripten/bind.h>

#include "psydapt.hpp"
#include "helper.hpp"

namespace em = emscripten;
namespace qp = psydapt::questplus;
using psydapt::questplus::NormCDF;

class EmNormCDF : public NormCDF
{
private:
    NormCDF::Params sanitize(em::val params)
    {
        NormCDF::Params p;
        // base params for all quest+
        em::val stim_sel_meth = params["stim_selection_method"];
        if (stim_sel_meth.isString())
        {
            std::string stim_str = stim_sel_meth.as<std::string>();
            qp::StimSelectionMethod s;
            if (stim_str == "MinEntropy")
            {
                s = qp::StimSelectionMethod::MinEntropy;
            }
            else if (stim_str == "MinNEntropy")
            {
                s = qp::StimSelectionMethod::MinNEntropy;
            }
            else
            {
                // TODO: error
                s = qp::StimSelectionMethod::MinEntropy;
            }
            p.stim_selection_method = s;
        }

        em::val par_est_meth = params["param_estimation_method"];
        if (par_est_meth.isString())
        {
            std::string par_str = par_est_meth.as<std::string>();
            qp::ParamEstimationMethod s;
            if (par_str == "Mean")
            {
                s = qp::ParamEstimationMethod::Mean;
            }
            else if (par_str == "Median")
            {
                s = qp::ParamEstimationMethod::Median;
            }
            else if (par_str == "Mode")
            {
                s = qp::ParamEstimationMethod::Mode;
            }
            else
            {
                s = qp::ParamEstimationMethod::Mean;
            }
            p.param_estimation_method = s;
        }
        convert(p.n, params["n"]);
        convert(p.max_consecutive_reps, params["max_consecutive_reps"]);
        convert(p.random_seed, params["random_seed"]);
        // end of base params
        // begin NormCDF-specific
        convert(p.stim_scale, params["stim_scale"]["value"]);

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
    bool update(int value)
    {
        return NormCDF::update(value);
    }
    bool update(int value, double stimulus)
    {
        return NormCDF::update(value, stimulus);
    }

    double next()
    {
        return NormCDF::next();
    }
};
