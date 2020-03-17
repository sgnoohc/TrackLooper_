#include "trkCore.h"

//__________________________________________________________________________________________
float simhit_p(unsigned int simhitidx)
{

    // |momentum| calculation

    float px = trk.simhit_px()[simhitidx];
    float py = trk.simhit_py()[simhitidx];
    float pz = trk.simhit_pz()[simhitidx];
    return sqrt(px*px + py*py + pz*pz);
}

//__________________________________________________________________________________________
float hitAngle(unsigned int simhitidx)
{

    // This is the angle calculation between position vector and the momentum vector

    float x = trk.simhit_x()[simhitidx];
    float y = trk.simhit_y()[simhitidx];
    float z = trk.simhit_z()[simhitidx];
    float r3 = sqrt(x*x + y*y + z*z);
    float px = trk.simhit_px()[simhitidx];
    float py = trk.simhit_py()[simhitidx];
    float pz = trk.simhit_pz()[simhitidx];
    float p = sqrt(px*px + py*py + pz*pz);
    float rdotp = x*px + y*py + z*pz;
    rdotp = rdotp / r3;
    rdotp = rdotp / p;
    float angle = acos(rdotp);
    return angle;
}

//__________________________________________________________________________________________
bool isMuonCurlingHit(unsigned int isimtrk, unsigned int ith_hit)
{

    // To assess whether the ith_hit for isimtrk is a "curling" hit

    // Retrieve the sim hit idx
    unsigned int simhitidx = trk.sim_simHitIdx()[isimtrk][ith_hit];

    // We're only concerned about hits in the outer tracker
    // This is more of a sanity check
    if (not (trk.simhit_subdet()[simhitidx] == 4 or trk.simhit_subdet()[simhitidx] == 5))
        return false;

    // Retrieve the sim hit pdgId
    int simhit_particle = trk.simhit_particle()[simhitidx];

    // If the hit is not muon then we can't tell anything
    if (abs(simhit_particle) != 13)
        return false;

    // Get the angle
    float angle = hitAngle(simhitidx);

    // If the angle is quite different then it's the last hit
    if (abs(angle) > 1.6)
        return true;

    // Afterwards, we check the energy loss
    //
    // If it is the first hit without any previous hit present,
    // we can't tell whether it is last hit or not
    // so we just say false to be conservative
    if (ith_hit == 0)
        return false;

    // Retrieve the module where the hit lies
    int detid = trk.simhit_detId()[simhitidx];
    SDL::Module module = SDL::Module(detid);

    // Calculate the momentum
    float p = simhit_p(simhitidx);

    // Find the previous simhit that is on the lower side of the module
    int simhitidx_previous = -999;
    for (unsigned int ith_back = 1; ith_back <= ith_hit; ith_back++)
    {
        // Retrieve the hit idx of ith_hit - ith_back;
        unsigned int simhitidx_previous_candidate = trk.sim_simHitIdx()[isimtrk][ith_hit-ith_back];

        if (not (trk.simhit_subdet()[simhitidx_previous_candidate] == 4 or trk.simhit_subdet()[simhitidx_previous_candidate] == 5))
            continue;

        if (not (trk.simhit_particle()[simhitidx_previous_candidate] == 13))
            continue;

        // Retrieve the module where the previous candidate hit lies
        int detid = trk.simhit_detId()[simhitidx_previous_candidate];
        SDL::Module module = SDL::Module(detid);

        // If the module is lower, then we get the index
        if (module.isLower())
        {
            simhitidx_previous = simhitidx_previous_candidate;
            break;
        }

    }

    // If no previous layer is found then can't do much
    if (simhitidx_previous == -999)
        return false;

    // Get the previous layer momentum
    float p_previous = simhit_p(simhitidx_previous);

    // Calculate the momentum loss
    float loss = fabs(p_previous - p) / p_previous;

    // If the momentum loss is large it is the last hit
    if (loss > 0.35)
        return true;

    // If it reaches this point again, we're not sure what this hit is
    // So we return false 
    return false;

}

//__________________________________________________________________________________________
bool hasAll12HitsWithNBarrelUsingModuleMap(unsigned int isimtrk, int nbarrel, bool usesimhits)
{

    // Select only tracks that left all 12 hits in the barrel
    std::array<std::vector<SDL::Module>, 6> layers_modules_barrel; // Watch out for duplicates in this vector, do not count with this for unique count.
    std::array<std::vector<SDL::Module>, 6> layers_modules_endcap; // Watch out for duplicates in this vector, do not count with this for unique count.

    std::vector<float> ps;

    for (unsigned int ith_hit = 0; ith_hit < trk.sim_simHitIdx()[isimtrk].size(); ++ith_hit)
    {

        // Retrieve the sim hit idx
        unsigned int simhitidx = trk.sim_simHitIdx()[isimtrk][ith_hit];

        // Select only the hits in the outer tracker
        if (not (trk.simhit_subdet()[simhitidx] == 4 or trk.simhit_subdet()[simhitidx] == 5))
            continue;

        if (not (trk.simhit_particle()[simhitidx] == trk.sim_pdgId()[isimtrk]))
            continue;

        if (isMuonCurlingHit(isimtrk, ith_hit))
            break;

        if (not usesimhits)
        {

            // list of reco hit matched to this sim hit
            for (unsigned int irecohit = 0; irecohit < trk.simhit_hitIdx()[simhitidx].size(); ++irecohit)
            {
                // Get the recohit type
                int recohittype = trk.simhit_hitType()[simhitidx][irecohit];

                // Consider only ph2 hits (i.e. outer tracker hits)
                if (recohittype == 4)
                {

                    int ihit = trk.simhit_hitIdx()[simhitidx][irecohit];

                    if (trk.ph2_subdet()[ihit] == 5)
                    {
                        layers_modules_barrel[trk.ph2_layer()[ihit] - 1].push_back(SDL::Module(trk.ph2_detId()[ihit]));
                    }
                    if (trk.ph2_subdet()[ihit] == 4)
                    {
                        layers_modules_endcap[trk.ph2_layer()[ihit] - 1].push_back(SDL::Module(trk.ph2_detId()[ihit]));
                    }

                }

            }

        }
        else
        {

            if (trk.simhit_hitIdx()[simhitidx].size() > 0)
            {

                if (trk.simhit_subdet()[simhitidx] == 5)
                {
                    layers_modules_barrel[trk.simhit_layer()[simhitidx] - 1].push_back(SDL::Module(trk.simhit_detId()[simhitidx]));
                }
                if (trk.simhit_subdet()[simhitidx] == 4)
                {
                    layers_modules_endcap[trk.simhit_layer()[simhitidx] - 1].push_back(SDL::Module(trk.simhit_detId()[simhitidx]));
                }
            }

            // // list of reco hit matched to this sim hit
            // for (unsigned int irecohit = 0; irecohit < trk.simhit_hitIdx()[simhitidx].size(); ++irecohit)
            // {
            //     // Get the recohit type
            //     int recohittype = trk.simhit_hitType()[simhitidx][irecohit];

            //     // Consider only ph2 hits (i.e. outer tracker hits)
            //     if (recohittype == 4)
            //     {

            //         int ihit = trk.simhit_hitIdx()[simhitidx][irecohit];

            //         if (trk.ph2_subdet()[ihit] == 5)
            //         {
            //             layers_modules_barrel[trk.ph2_layer()[ihit] - 1].push_back(SDL::Module(trk.ph2_detId()[ihit]));
            //         }
            //         if (trk.ph2_subdet()[ihit] == 4)
            //         {
            //             layers_modules_endcap[trk.ph2_layer()[ihit] - 1].push_back(SDL::Module(trk.ph2_detId()[ihit]));
            //         }

            //     }

            // }

        }

    }

    // Aggregating good pair modules (i.e. a double module with each side having non-zero reco hits.)
    std::array<std::vector<unsigned int>, 6> layers_good_paired_modules; // Watch out for duplicates in this vector, do not count with this for unique count.

    for (int logical_ilayer = 0; logical_ilayer < 6; ++logical_ilayer)
    {
        // Raw layer number
        bool is_ilayer_barrel = logical_ilayer < nbarrel;
        int raw_ilayer = is_ilayer_barrel ? logical_ilayer: logical_ilayer - nbarrel;
        const std::array<std::vector<SDL::Module>, 6>& layers_modules = is_ilayer_barrel ? layers_modules_barrel : layers_modules_endcap;

        // Then get the module in the ilayer and check that it has a good module pair
        // Loop over modules in the given raw_ilayer and match the pairs and if a good pair of modules have hits in each module
        // then save the lower modules to layers_good_paired_modules.
        // NOTE there may be duplicates being pushed to layers_good_paired_modules
        // Do not count with these vectors
        for (unsigned imod = 0; imod < layers_modules[raw_ilayer].size(); ++imod)
        {
            for (unsigned jmod = imod + 1; jmod < layers_modules[raw_ilayer].size(); ++jmod)
            {
                // if two modules are a good pair
                if (layers_modules[raw_ilayer][imod].partnerDetId() == layers_modules[raw_ilayer][jmod].detId())
                {
                    // add the lower module one to the good_paired_modules list
                    if (layers_modules[raw_ilayer][imod].isLower())
                    {
                        if (std::find(
                                    layers_good_paired_modules[logical_ilayer].begin(),
                                    layers_good_paired_modules[logical_ilayer].end(),
                                    layers_modules[raw_ilayer][imod].detId()) == layers_good_paired_modules[logical_ilayer].end())
                            layers_good_paired_modules[logical_ilayer].push_back(layers_modules[raw_ilayer][imod].detId());
                    }
                    else
                    {
                        if (std::find(
                                    layers_good_paired_modules[logical_ilayer].begin(),
                                    layers_good_paired_modules[logical_ilayer].end(),
                                    layers_modules[raw_ilayer][imod].partnerDetId()) == layers_good_paired_modules[logical_ilayer].end())
                        layers_good_paired_modules[logical_ilayer].push_back(layers_modules[raw_ilayer][imod].partnerDetId());
                    }
                }
            }
        }
    }

    return checkModuleConnectionsAreGood(layers_good_paired_modules);

}

//__________________________________________________________________________________________
bool checkModuleConnectionsAreGood(std::array<std::vector<unsigned int>, 6>& layers_good_paired_modules)
{
    // Dumbest possible solution
    for (auto& module0 : layers_good_paired_modules[0])
    {
        const std::vector<unsigned int>& connectedModule1s = SDL::moduleConnectionMap.getConnectedModuleDetIds(module0);
        for (auto& module1 : layers_good_paired_modules[1])
        {
            if (std::find(connectedModule1s.begin(), connectedModule1s.end(), module1) == connectedModule1s.end())
                break;
            const std::vector<unsigned int>& connectedModule2s = SDL::moduleConnectionMap.getConnectedModuleDetIds(module1);
            for (auto& module2 : layers_good_paired_modules[2])
            {
                if (std::find(connectedModule2s.begin(), connectedModule2s.end(), module2) == connectedModule2s.end())
                    break;
                const std::vector<unsigned int>& connectedModule3s = SDL::moduleConnectionMap.getConnectedModuleDetIds(module2);
                for (auto& module3 : layers_good_paired_modules[3])
                {
                    if (std::find(connectedModule3s.begin(), connectedModule3s.end(), module3) == connectedModule3s.end())
                        break;
                    const std::vector<unsigned int>& connectedModule4s = SDL::moduleConnectionMap.getConnectedModuleDetIds(module3);
                    for (auto& module4 : layers_good_paired_modules[4])
                    {
                        if (std::find(connectedModule4s.begin(), connectedModule4s.end(), module4) == connectedModule4s.end())
                            break;
                        const std::vector<unsigned int>& connectedModule5s = SDL::moduleConnectionMap.getConnectedModuleDetIds(module4);
                        for (auto& module5 : layers_good_paired_modules[5])
                        {
                            if (std::find(connectedModule5s.begin(), connectedModule5s.end(), module5) == connectedModule5s.end())
                                break;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

//__________________________________________________________________________________________
bool hasAll12HitsWithNBarrel(unsigned int isimtrk, int nbarrel)
{

    // Select only tracks that left all 12 hits in the barrel
    std::array<std::vector<SDL::Module>, 6> layers_modules_barrel;
    std::array<std::vector<SDL::Module>, 6> layers_modules_endcap;

    std::vector<float> ps;

    for (unsigned int ith_hit = 0; ith_hit < trk.sim_simHitIdx()[isimtrk].size(); ++ith_hit)
    {

        // Retrieve the sim hit idx
        unsigned int simhitidx = trk.sim_simHitIdx()[isimtrk][ith_hit];

        // Select only the hits in the outer tracker
        if (not (trk.simhit_subdet()[simhitidx] == 4 or trk.simhit_subdet()[simhitidx] == 5))
            continue;

        // if (not (trk.simhit_particle()[simhitidx] == trk.sim_pdgId()[isimtrk]))
        //     continue;

        if (isMuonCurlingHit(isimtrk, ith_hit))
            break;

        // list of reco hit matched to this sim hit
        for (unsigned int irecohit = 0; irecohit < trk.simhit_hitIdx()[simhitidx].size(); ++irecohit)
        {
            // Get the recohit type
            int recohittype = trk.simhit_hitType()[simhitidx][irecohit];

            // Consider only ph2 hits (i.e. outer tracker hits)
            if (recohittype == 4)
            {

                int ihit = trk.simhit_hitIdx()[simhitidx][irecohit];

                if (trk.ph2_subdet()[ihit] == 5)
                {
                    layers_modules_barrel[trk.ph2_layer()[ihit] - 1].push_back(SDL::Module(trk.ph2_detId()[ihit]));
                }
                if (trk.ph2_subdet()[ihit] == 4)
                {
                    layers_modules_endcap[trk.ph2_layer()[ihit] - 1].push_back(SDL::Module(trk.ph2_detId()[ihit]));
                }

            }

        }

    }

    std::array<bool, 6> has_good_pair_by_layer_barrel;
    has_good_pair_by_layer_barrel[0] = false;
    has_good_pair_by_layer_barrel[1] = false;
    has_good_pair_by_layer_barrel[2] = false;
    has_good_pair_by_layer_barrel[3] = false;
    has_good_pair_by_layer_barrel[4] = false;
    has_good_pair_by_layer_barrel[5] = false;

    std::array<bool, 6> has_good_pair_by_layer_endcap;
    has_good_pair_by_layer_endcap[0] = false;
    has_good_pair_by_layer_endcap[1] = false;
    has_good_pair_by_layer_endcap[2] = false;
    has_good_pair_by_layer_endcap[3] = false;
    has_good_pair_by_layer_endcap[4] = false;
    has_good_pair_by_layer_endcap[5] = false;

    bool has_good_pair_all_layer = true;

    for (int ilayer = 0; ilayer < 6; ++ilayer)
    {

        bool has_good_pair = false;

        if (ilayer < nbarrel)
        {

            for (unsigned imod = 0; imod < layers_modules_barrel[ilayer].size(); ++imod)
            {
                for (unsigned jmod = imod + 1; jmod < layers_modules_barrel[ilayer].size(); ++jmod)
                {
                    if (layers_modules_barrel[ilayer][imod].partnerDetId() == layers_modules_barrel[ilayer][jmod].detId())
                        has_good_pair = true;
                }
            }

        }
        else
        {

            int endcap_ilayer = ilayer - nbarrel;

            for (unsigned imod = 0; imod < layers_modules_endcap[endcap_ilayer].size(); ++imod)
            {
                for (unsigned jmod = imod + 1; jmod < layers_modules_endcap[endcap_ilayer].size(); ++jmod)
                {
                    if (layers_modules_endcap[endcap_ilayer][imod].partnerDetId() == layers_modules_endcap[endcap_ilayer][jmod].detId())
                        has_good_pair = true;
                }
            }

        }

        if (not has_good_pair)
            has_good_pair_all_layer = false;

        if (ilayer < nbarrel)
            has_good_pair_by_layer_barrel[ilayer] = has_good_pair;
        else
            has_good_pair_by_layer_endcap[ilayer] = has_good_pair;

    }


    float pt = trk.sim_pt()[isimtrk];
    float eta = trk.sim_eta()[isimtrk];

    // if (abs((trk.sim_pt()[isimtrk] - 0.71710)) < 0.00001)
    // {
    //     std::cout << std::endl;
    //     std::cout <<  " has_good_pair_by_layer[0]: " << has_good_pair_by_layer[0] <<  " has_good_pair_by_layer[1]: " << has_good_pair_by_layer[1] <<  " has_good_pair_by_layer[2]: " << has_good_pair_by_layer[2] <<  " has_good_pair_by_layer[3]: " << has_good_pair_by_layer[3] <<  " has_good_pair_by_layer[4]: " << has_good_pair_by_layer[4] <<  " has_good_pair_by_layer[5]: " << has_good_pair_by_layer[5] <<  " pt: " << pt <<  " eta: " << eta <<  std::endl;
    // }

    return has_good_pair_all_layer;

}

//__________________________________________________________________________________________
bool hasAll12HitsInBarrel(unsigned int isimtrk)
{

    // Select only tracks that left all 12 hits in the barrel
    std::array<std::vector<SDL::Module>, 6> layers_modules;

    std::vector<float> ps;

    for (unsigned int ith_hit = 0; ith_hit < trk.sim_simHitIdx()[isimtrk].size(); ++ith_hit)
    {

        // Retrieve the sim hit idx
        unsigned int simhitidx = trk.sim_simHitIdx()[isimtrk][ith_hit];

        // Select only the hits in the outer tracker
        if (not (trk.simhit_subdet()[simhitidx] == 4 or trk.simhit_subdet()[simhitidx] == 5))
            continue;

        // if (not (trk.simhit_particle()[simhitidx] == trk.sim_pdgId()[isimtrk]))
        //     continue;

        if (isMuonCurlingHit(isimtrk, ith_hit))
            break;

        // list of reco hit matched to this sim hit
        for (unsigned int irecohit = 0; irecohit < trk.simhit_hitIdx()[simhitidx].size(); ++irecohit)
        {
            // Get the recohit type
            int recohittype = trk.simhit_hitType()[simhitidx][irecohit];

            // Consider only ph2 hits (i.e. outer tracker hits)
            if (recohittype == 4)
            {

                int ihit = trk.simhit_hitIdx()[simhitidx][irecohit];

                if (trk.ph2_subdet()[ihit] == 5)
                {
                    layers_modules[trk.ph2_layer()[ihit] - 1].push_back(SDL::Module(trk.ph2_detId()[ihit]));
                }

            }

        }

    }

    std::array<bool, 6> has_good_pair_by_layer;
    has_good_pair_by_layer[0] = false;
    has_good_pair_by_layer[1] = false;
    has_good_pair_by_layer[2] = false;
    has_good_pair_by_layer[3] = false;
    has_good_pair_by_layer[4] = false;
    has_good_pair_by_layer[5] = false;

    bool has_good_pair_all_layer = true;

    for (int ilayer = 0; ilayer < 6; ++ilayer)
    {

        bool has_good_pair = false;

        for (unsigned imod = 0; imod < layers_modules[ilayer].size(); ++imod)
        {
            for (unsigned jmod = imod + 1; jmod < layers_modules[ilayer].size(); ++jmod)
            {
                if (layers_modules[ilayer][imod].partnerDetId() == layers_modules[ilayer][jmod].detId())
                    has_good_pair = true;
            }
        }

        if (not has_good_pair)
            has_good_pair_all_layer = false;

        has_good_pair_by_layer[ilayer] = has_good_pair;

    }

    float pt = trk.sim_pt()[isimtrk];
    float eta = trk.sim_eta()[isimtrk];

    // if (abs((trk.sim_pt()[isimtrk] - 0.71710)) < 0.00001)
    // {
    //     std::cout << std::endl;
    //     std::cout <<  " has_good_pair_by_layer[0]: " << has_good_pair_by_layer[0] <<  " has_good_pair_by_layer[1]: " << has_good_pair_by_layer[1] <<  " has_good_pair_by_layer[2]: " << has_good_pair_by_layer[2] <<  " has_good_pair_by_layer[3]: " << has_good_pair_by_layer[3] <<  " has_good_pair_by_layer[4]: " << has_good_pair_by_layer[4] <<  " has_good_pair_by_layer[5]: " << has_good_pair_by_layer[5] <<  " pt: " << pt <<  " eta: " << eta <<  std::endl;
    // }

    return has_good_pair_all_layer;

}



bool hasAtLeastOneHitPairinEndcapLikeTiltedModule(unsigned short layer, unsigned int isimtrk)
{
    //Checking done only for the layer specified by "layer", otherwise function returns true always
    std::vector<SDL::Module> layer_modules;


    for (unsigned int ith_hit = 0; ith_hit < trk.sim_simHitIdx()[isimtrk].size(); ++ith_hit)
    {

        // Retrieve the sim hit idx
        unsigned int simhitidx = trk.sim_simHitIdx()[isimtrk][ith_hit];

        // Select only the hits in the outer tracker
        if (not (trk.simhit_subdet()[simhitidx] == 4 or trk.simhit_subdet()[simhitidx] == 5))
            continue;

        if (isMuonCurlingHit(isimtrk, ith_hit))
            break;

        // list of reco hit matched to this sim hit
        for (unsigned int irecohit = 0; irecohit < trk.simhit_hitIdx()[simhitidx].size(); ++irecohit)
        {
            // Get the recohit type
            int recohittype = trk.simhit_hitType()[simhitidx][irecohit];

            // Consider only ph2 hits (i.e. outer tracker hits)
            if (recohittype == 4)
            {

                int ihit = trk.simhit_hitIdx()[simhitidx][irecohit];


                if(trk.ph2_layer()[ihit] == layer and trk.ph2_subdet()[ihit] == 5 and (not SDL::MiniDoublet::useBarrelLogic(trk.ph2_detId()[ihit])))
                {
                    layer_modules.push_back(SDL::Module(trk.ph2_detId()[ihit]));

                }

            }

        }
    }
    //Check if there is at least one pair in an endcap like tilted module
    //in the layer denoted by the parameter "layer"

    bool hasTiltedPairAtLayer = false;

    for (unsigned imod = 0; imod < layer_modules.size(); ++imod)
    {

        for (unsigned jmod = imod + 1; jmod < layer_modules.size(); ++jmod)
        {
            if (layer_modules[imod].partnerDetId() == layer_modules[jmod].detId())
            {
                hasTiltedPairAtLayer = true;
            }
                
        }
    }

    return hasTiltedPairAtLayer;
}



//__________________________________________________________________________________________
bool isMTVMatch(unsigned int isimtrk, std::vector<unsigned int> hit_idxs)
{
    std::vector<unsigned int> sim_trk_ihits;
    for (auto& i_simhit_idx : trk.sim_simHitIdx()[isimtrk])
    {
        for (auto& ihit : trk.simhit_hitIdx()[i_simhit_idx])
        {
            sim_trk_ihits.push_back(ihit);
        }
    }

    std::vector<unsigned int> v_intersection;
 
    std::set_intersection(sim_trk_ihits.begin(), sim_trk_ihits.end(),
                          hit_idxs.begin(), hit_idxs.end(),
                          std::back_inserter(v_intersection));

    // If 75% of 12 hits have been found than it is matched
    return (v_intersection.size() > 9);
}

//__________________________________________________________________________________________
bool is75percentFromSimMatchedHits(std::vector<unsigned int> hitidxs, int pdgid)
{
    std::vector<unsigned int> hitidxs_w_matched_pdgid;
    for (auto& i_reco_hit : hitidxs)
    {
        bool matched = false;
        for (auto& i_simhit_idx : trk.ph2_simHitIdx()[i_reco_hit])
        {
            matched = true;
            break;
            // int particle_id = trk.simhit_particle()[i_simhit_idx];
            // if (abs(pdgid) == abs(particle_id))
            // {
            //     matched = true;
            //     break;
            // }
        }
        if (matched)
            hitidxs_w_matched_pdgid.push_back(i_reco_hit);
    }

    std::vector<unsigned int> v_intersection;
 
    std::set_intersection(hitidxs_w_matched_pdgid.begin(), hitidxs_w_matched_pdgid.end(),
                          hitidxs.begin(), hitidxs.end(),
                          std::back_inserter(v_intersection));

    // If 75% of 12 hits have been found than it is matched
    return (v_intersection.size() >= 9);

}

//__________________________________________________________________________________________
TVector3 linePropagateR(const TVector3& r3, const TVector3& p3, double rDest, int& status, bool useClosest, bool verbose)
{
  double rt = r3.Pt();
  double d = rDest - rt;

  double dotPR2D = r3.x()*p3.x() + r3.y()*p3.y();

  double pt = p3.Pt();
  double p =  p3.Mag();
  
  // r3 + p3/p*x*|d| = dest : dest.t = rt + d <=> rt^2 + 2*dotPR2D/p*x*|d| + pt^2/p^2*x^2*d^2 = rt^2 + 2*rt*d + d^2
  // 2*dotPR2D/p*|d|* x + pt^2/p^2*d^2* x^2 - ( 2*rt*d + d^2) = 0
  // 2*dotPR2D/p/|d|* x + pt^2/p^2* x^2 - ( 2*rt/d + 1) = 0
  // x^2 + 2*dotPR2D/p/|d|*(p/pt)^2* x  - ( 2*rt/d + 1)*(p/pt)^2 = 0
  // - dotPR2D/p/|d|*(p/pt)^2  +/- sqrt( (dotPR2D/p/|d|*(p/pt)^2)^2 + ( 2*rt/d + 1)*(p/pt)^2 )
  // (p/pt)*( - dotPR2D/pt/|d|  +/- sqrt( (dotPR2D/pt/|d| )^2 + ( 2*rt/d + 1) ) )
  double bb = dotPR2D/pt/std::abs(d);
  double disc = bb*bb + (2.*rt/d + 1.);
  status = 0;
  if (disc < 0){
    status = 1;
    return r3;
  }
  double dSign = useClosest ? 1. : -1.;
  double xxP = (p/pt)*( sqrt(bb*bb + (2.*rt/d + 1.)) - bb);
  double xxM = (p/pt)*( - sqrt(bb*bb + (2.*rt/d + 1.)) - bb);
  double xx;
  if (useClosest){
    xx = std::abs(xxP) < std::abs(xxM) ? xxP : xxM;
  } else {
    xx = std::abs(xxP) < std::abs(xxM) ? xxM : xxP;
  }
  TVector3 dest = r3 + p3*(std::abs(d)/p)*xx;
  if (verbose || std::abs(dest.Pt() - rDest)>0.001){
    std::cout<<"linePropagateR "<<r3.Pt()<<" "<<r3.Phi()<<" "<<r3.z()<<" "<<pt<<" "<<p
	     <<" "<<d<<" "<<r3.x()*p3.x()<<" "<<r3.y()*p3.y()<<" "<<dotPR2D<<" "<<bb<<" "<<(2.*rt/d + 1.)<<" "<<bb*bb + (2.*rt/d + 1.)
	     <<" => "<<rDest
	     <<" => "<<dest.Pt()<<" "<<dest.Phi()<<" "<<dest.z()
	     <<std::endl;
  }
  return dest;

}

std::pair<TVector3,TVector3> helixPropagateApproxR(const TVector3& r3, const TVector3& p3, double rDest, int q, int& status, bool useClosest, bool verbose)
{
  double epsilon = 0.001;
  double p = p3.Mag();
  double kap = (2.99792458e-3*3.8*q/p);
  
  auto lastR3 = r3;
  auto lastT3 = p3.Unit();
  int nIts = 7;

  while (std::abs(lastR3.Perp() - rDest) > epsilon && nIts >= 0){
    auto lineEst = linePropagateR(lastR3, lastT3*p, rDest, status, useClosest, verbose);
    if (status){
      if (verbose) std::cout<<" failed with status "<<status<<std::endl;
      return { lineEst, lastT3*p};
    }
    if (q==0) return {lineEst, lastT3*p};
    
    double dir = (lineEst.x() - lastR3.x())*lastT3.x() + (lineEst.y() - lastR3.y())*lastT3.y() > 0 ? 1. : -1;
    double dS = (lineEst - lastR3).Mag()*dir;
    double phi = kap*dS;
    if (std::abs(phi) > 1) {
      if (verbose) std::cout<<" return line for very large angle "<<status<<std::endl;
      return { lineEst, lastT3*p};
    }
    double alpha = 1 - sin(phi)/phi;
    double beta = (1 - cos(phi))/phi;
    
    TVector3 tau = lastT3; 
    
    TVector3 hEstR3(tau.x()*(1.-alpha) + tau.y()*beta, tau.y()*(1.-alpha) - tau.x()*beta, tau.z());
    hEstR3 *= dS;
    hEstR3 += lastR3;
    lastR3 = hEstR3;
    
    TVector3 hEstT3(tau.x()*cos(phi) + tau.y()*sin(phi), tau.y()*cos(phi) - tau.x()*sin(phi), tau.z());
    lastT3 = hEstT3;
    --nIts;
    if (verbose){
      std::cout<<"nIts "<<nIts<<" rDest "<<rDest<<" dS "<<dS<<" phi "<<phi
	       <<" r3In ("<<r3.Pt()<<", "<<r3.Eta()<<", "<<r3.Phi()<<")"
	       <<" p3In ("<<p3.Pt()<<", "<<p3.Eta()<<", "<<p3.Phi()<<")"
	       <<" r3out ("<<lastR3.Pt()<<", "<<lastR3.Eta()<<", "<<lastR3.Phi()<<")"
	       <<" p3Out ("<<lastT3.Pt()*p<<", "<<lastT3.Eta()<<", "<<lastT3.Phi()<<")"
	       <<std::endl;
    }
  }
  status = (std::abs(lastR3.Perp() - rDest) > epsilon);
  return {lastR3, lastT3*p};
  
}


void fitCircle(std::vector<float> xs, std::vector<float> ys)
{

    TCanvas *c1 = new TCanvas("c1","c1",600,600);
    c1->SetGrid();

    // Generate graph that contains the data
    TGraph* gr = new TGraph(xs.size());
    for (unsigned int i = 0; i < xs.size(); ++i)
    {
        gr->SetPoint(i,xs[i],ys[i]);
    }

    c1->DrawFrame(-120,-120,120,120);
    gr->Draw("p");

    auto chi2Function = [&](const Double_t *par) {
        // minimisation function computing the sum of squares of residuals
        // looping at the graph points
        Int_t np = gr->GetN();
        Double_t f = 0;
        Double_t *x = gr->GetX();
        Double_t *y = gr->GetY();
        for (Int_t i=0;i<np;i++) {
            Double_t u = x[i] - par[0];
            Double_t v = y[i] - par[1];
            Double_t dr = par[2] - std::sqrt(u*u+v*v);
            f += dr*dr;
        }
        return f;
    };

    // wrap chi2 funciton in a function object for the fit
    // 3 is the number of fit parameters (size of array par)
    ROOT::Math::Functor fcn(chi2Function,3);
    ROOT::Fit::Fitter  fitter;
    double pStart[3] = {0,0,1};
    fitter.SetFCN(fcn, pStart);
    fitter.Config().ParSettings(0).SetName("x0");
    fitter.Config().ParSettings(1).SetName("y0");
    fitter.Config().ParSettings(2).SetName("R");

    // do the fit 
    bool ok = fitter.FitFCN();
    if (!ok) {
        Error("line3Dfit","Line3D Fit failed");
    }   

    const ROOT::Fit::FitResult & result = fitter.Result();

    result.Print(std::cout);

    //Draw the circle on top of the points
    TArc *arc = new TArc(result.Parameter(0),result.Parameter(1),result.Parameter(2));
    arc->SetLineColor(kRed);
    arc->SetLineWidth(4);
    arc->SetFillColorAlpha(0, 0.35);
    arc->Draw();
    c1->SaveAs("result.pdf");

}
