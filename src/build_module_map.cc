#include "build_module_map.h"

void build_module_map()
{

    // connection information
    std::ofstream module_connection_log_output;
    module_connection_log_output.open("conn.txt");

    // Looping input file
    while (ana.looper.nextEvent())
    {

        if (ana.specific_event_index >= 0)
        {
            if ((int)ana.looper.getCurrentEventIndex() != ana.specific_event_index)
                continue;
        }

        // If splitting jobs are requested then determine whether to process the event or not based on remainder
        if (ana.nsplit_jobs > 0 and ana.job_index > 0)
        {
            if (ana.looper.getNEventsProcessed() % ana.nsplit_jobs != (unsigned int) ana.job_index)
                continue;
        }

        if (ana.verbose) std::cout <<  " ana.looper.getCurrentEventIndex(): " << ana.looper.getCurrentEventIndex() <<  std::endl;

        // for (auto&& [isimtrk, simhitidxs] : iter::enumerate(trk.sim_simHitIdx()))
        // {
        //     std::cout <<  " isimtrk: " << isimtrk <<  std::endl;
        //     for (auto&& [isimhit, simhitidx] : iter::enumerate(iter::filter([&] (int i)
        //                     { return (trk.simhit_subdet()[i] == 4 or trk.simhit_subdet()[i] == 5) and trk.simhit_particle()[i] == trk.sim_pdgId()[isimtrk]; },
        //                     simhitidxs)))
        //     {
        //         std::cout << std::setw(12) << trk.sim_pt()[isimtrk] << " ";
        //         std::cout << std::setw(12) << trk.simhit_tof()[simhitidx] << " ";
        //         std::cout << std::setw(12) << trk.simhit_tof()[simhitidx] / sqrt(pow(trk.simhit_x()[simhitidx],2)+pow(trk.simhit_y()[simhitidx],2)+pow(trk.simhit_z()[simhitidx],2)) << " ";
        //         std::cout << std::setw(12) << (trk.simhit_subdet()[simhitidx]==4)*(6) + trk.simhit_layer()[simhitidx] << " ";
        //         std::cout << std::setw(12) << sqrt(pow(trk.simhit_px()[simhitidx],2)+pow(trk.simhit_py()[simhitidx],2)+pow(trk.simhit_pz()[simhitidx],2)) << " ";
        //         std::cout << std::setw(12) << trk.simhit_eloss()[simhitidx] << " ";
        //         std::cout << std::endl;
        //     }
        // }

        // printModuleConnections(module_connection_log_output);

    }
}

void printModuleConnections(std::ofstream& ostrm)
{
    // *****************************************************
    // Print module -> module connection info from sim track
    // *****************************************************

    // Loop over sim-tracks and per sim-track aggregate good hits (i.e. matched with particle ID)
    // and only use those hits, and run mini-doublet reco algorithm on the sim-track-matched-reco-hits
    for (unsigned int isimtrk = 0; isimtrk < trk.sim_q().size(); ++isimtrk)
    {

        // Select only muon tracks
        if (abs(trk.sim_pdgId()[isimtrk]) != 13)
            continue;

        if (trk.sim_pt()[isimtrk] < 1)
            continue;

        std::vector<int> layers;
        std::vector<int> subdets;
        std::vector<int> detids;
        std::vector<float> ps;

        // loop over the simulated hits
        for (auto& simhitidx : trk.sim_simHitIdx()[isimtrk])
        {

            // Select only the hits in the outer tracker
            if (not (trk.simhit_subdet()[simhitidx] == 4 or trk.simhit_subdet()[simhitidx] == 5))
                continue;

            int simhit_particle = trk.simhit_particle()[simhitidx];
            int detid = trk.simhit_detId()[simhitidx];
            int layer = trk.simhit_layer()[simhitidx];
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
            int subdet = trk.simhit_subdet()[simhitidx];
            int trkidx = trk.simhit_simTrkIdx()[simhitidx];
            SDL::Module module = SDL::Module(detid);

            // Select only the sim hits that is matched to the muon
            if (abs(simhit_particle) != 13)
                continue;

            // std::cout <<  " layer: " << layer <<  " subdet: " << subdet <<  " simhit_particle: " << simhit_particle <<  " x: " << x <<  " y: " << y <<  " z: " << z <<  " r3: " << r3 <<  " px: " << px <<  " py: " << py <<  " pz: " << pz <<  " p: " << p <<  " angle: " << angle <<  " trkidx: " << trkidx <<  " module.isLower(): " << module.isLower() <<  " detid: " << detid <<  std::endl;

            // if (abs(angle) > 1.6)
            //     break;

            if (ps.size() > 0)
            {
                float loss = fabs(ps.back() - p) / ps.back();
                if (loss > 0.35)
                    break;
            }

            // Access hits on the S side of the PS modules in the endcaps and get three numbers, (detId, x, y)
            if (module.isLower())
            {
                layers.push_back(layer);
                subdets.push_back(subdet);
                detids.push_back(detid);
                ps.push_back(p);
            }

        }

        // std::cout << "momentums: ";
        // for (auto& p : ps)
        // {
        //     std::cout << p << " ";
        // }
        // std::cout << std::endl;

        if (layers.size() > 0)
        {

            // std::cout <<  " trk.sim_pt()[isimtrk]: " << trk.sim_pt()[isimtrk] <<  " trk.sim_phi()[isimtrk]: " << trk.sim_phi()[isimtrk] <<  " trk.sim_eta()[isimtrk]: " << trk.sim_eta()[isimtrk] <<  " trk.sim_pca_dz()[isimtrk]: " << trk.sim_pca_dz()[isimtrk] <<  " trk.sim_pca_dxy()[isimtrk]: " << trk.sim_pca_dxy()[isimtrk] <<  " trk.sim_pca_lambda()[isimtrk]: " << trk.sim_pca_lambda()[isimtrk] <<  " trk.sim_pca_cotTheta()[isimtrk]: " << trk.sim_pca_cotTheta()[isimtrk] <<  " trk.sim_pca_phi()[isimtrk]: " << trk.sim_pca_phi()[isimtrk] <<  std::endl;
            ostrm << "moduleconnection: ";
            for (unsigned int i = 0; i < layers.size(); ++i)
            {
                ostrm << "(" << layers[i] << "," << subdets[i] << "," << detids[i] << "," << SDL::Module(detids[i]).partnerDetId() << ");";
            }
            ostrm << std::endl;
            // ostrm << trk.event() << " " << isimtrk << " ";
            // for (unsigned int i = 0; i < layers.size(); ++i)
            // {
            //     ostrm << detids[i] << "," << SDL::Module(detids[i]).partnerDetId();
            //     if (i != layers.size() - 1)
            //         ostrm << ",";
            // }
            // ostrm << std::endl;

            // // std::cout <<  " trk.sim_pt()[isimtrk]: " << trk.sim_pt()[isimtrk] <<  " trk.sim_phi()[isimtrk]: " << trk.sim_phi()[isimtrk] <<  " trk.sim_eta()[isimtrk]: " << trk.sim_eta()[isimtrk] <<  " trk.sim_pca_dz()[isimtrk]: " << trk.sim_pca_dz()[isimtrk] <<  " trk.sim_pca_dxy()[isimtrk]: " << trk.sim_pca_dxy()[isimtrk] <<  " trk.sim_pca_lambda()[isimtrk]: " << trk.sim_pca_lambda()[isimtrk] <<  " trk.sim_pca_cotTheta()[isimtrk]: " << trk.sim_pca_cotTheta()[isimtrk] <<  " trk.sim_pca_phi()[isimtrk]: " << trk.sim_pca_phi()[isimtrk] <<  std::endl;
            // std::cout << "moduleconnection: ";
            // for (unsigned int i = 0; i < layers.size(); ++i)
            // {
            //     std::cout << "(" << layers[i] << "," << subdets[i] << "," << detids[i] << "," << SDL::Module(detids[i]).partnerDetId() << ");";
            // }
            // std::cout << std::endl;
            // std::cout << trk.event() << " " << isimtrk << " ";
            // for (unsigned int i = 0; i < layers.size(); ++i)
            // {
            //     std::cout << detids[i] << "," << SDL::Module(detids[i]).partnerDetId();
            //     if (i != layers.size() - 1)
            //         std::cout << ",";
            // }
            // std::cout << std::endl;

        }

    }
}
