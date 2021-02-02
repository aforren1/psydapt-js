#include <string>
#include <emscripten/bind.h>
#include <optional>

#include "psydapt.hpp"

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
        em::val n = params["n"];
        if (n.isNumber())
        {
            p.n = n.as<unsigned int>();
        }
        em::val max_consecutive_reps = params["max_consecutive_reps"];
        if (max_consecutive_reps.isNumber())
        {
            p.max_consecutive_reps = max_consecutive_reps.as<unsigned int>();
        }
        em::val random_seed = params["random_seed"];
        if (random_seed.isNumber())
        {
            p.random_seed = random_seed.as<unsigned int>();
        }
        // end of base params
        // begin NormCDF-specific
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

        em::val intensity = params["intensity"];
        if (intensity.isArray())
        {
            p.intensity = em::convertJSArrayToNumberVector<double>(intensity);
        }
        em::val location = params["location"];
        if (location.isArray())
        {
            p.location = em::convertJSArrayToNumberVector<double>(location);
        }
        em::val scale = params["scale"];
        if (scale.isArray())
        {
            p.scale = em::convertJSArrayToNumberVector<double>(scale);
        }
        em::val lower_asymptote = params["lower_asymptote"];
        if (lower_asymptote.isArray())
        {
            p.lower_asymptote = em::convertJSArrayToNumberVector<double>(lower_asymptote);
        }
        em::val lapse_rate = params["lapse_rate"];
        if (lapse_rate.isArray())
        {
            p.lapse_rate = em::convertJSArrayToNumberVector<double>(lapse_rate);
        }
        // priors
        em::val location_prior = params["location_prior"];
        if (location_prior.isArray())
        {
            p.location_prior = em::convertJSArrayToNumberVector<double>(location_prior);
        }
        em::val scale_prior = params["scale_prior"];
        if (scale_prior.isArray())
        {
            p.scale_prior = em::convertJSArrayToNumberVector<double>(scale_prior);
        }
        em::val lower_asymptote_prior = params["lower_asymptote_prior"];
        if (lower_asymptote_prior.isArray())
        {
            p.lower_asymptote_prior = em::convertJSArrayToNumberVector<double>(lower_asymptote_prior);
        }
        em::val lapse_rate_prior = params["lapse_rate_prior"];
        if (lapse_rate_prior.isArray())
        {
            p.lapse_rate_prior = em::convertJSArrayToNumberVector<double>(lapse_rate_prior);
        }
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
