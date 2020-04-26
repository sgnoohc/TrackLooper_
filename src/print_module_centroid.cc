#include "print_module_centroid.h"

void print_module_centroid()
{

    // connection information
    std::ofstream module_connection_log_output;
    module_connection_log_output.open("data/centroid.txt");

    std::vector<unsigned int> detids;
    std::map<unsigned int, int> detid_count;
    std::map<unsigned int, float> detid_x;
    std::map<unsigned int, float> detid_y;
    std::map<unsigned int, float> detid_z;


    // Looping input file
    while (ana.looper.nextEvent())
    {

        if (not (goodEvent()))
            continue;

        for (auto&& [isimhit, detid] : iter::enumerate(trk.simhit_detId()))
        {
            if (not (trk.simhit_subdet()[isimhit] == 4 or trk.simhit_subdet()[isimhit] == 5))
                continue;
            detid_count[detid]++;
            detid_x[detid] += trk.simhit_x()[isimhit];
            detid_y[detid] += trk.simhit_y()[isimhit];
            detid_z[detid] += trk.simhit_z()[isimhit];
            if (std::find(detids.begin(), detids.end(), detid) == detids.end())
                detids.push_back(detid);
        }
    }

    for (auto&& detid : iter::sorted(detids))
    {
        SDL::Module module(detid);
        module_connection_log_output << detid << ",";
        module_connection_log_output << detid_x[detid]/detid_count[detid] << ",";
        module_connection_log_output << detid_y[detid]/detid_count[detid] << ",";
        module_connection_log_output << detid_z[detid]/detid_count[detid] << ",";
        module_connection_log_output << detid_count[detid] << ",";
        module_connection_log_output << module.layer() + (module.subdet() == 4)*6;
        module_connection_log_output << std::endl;
    }

}

