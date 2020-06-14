# include "StudyChargeClassification.h"

StudyChargeClassification :: StudyChargeClassification(const char* studyName)
{
    studyName = studyName;
}

void StudyChargeClassification::bookStudy()
{
    //pt bins
    for(int i = 0; i <=250; i++)
    {
        ptbins.push_back(i * (50.0-0.5)/250) ; 
    }

    ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives"),ptbins,[&](){return truePositives;});
    ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives"),ptbins,[&](){return trueNegatives;});
    ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives"),ptbins,[&](){return falsePositives;});
    ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives"),ptbins,[&](){return falseNegatives;});
    ana.histograms.addVecHistogram(TString::Format("track_pt"),ptbins,[&](){return trackPt;});

    ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives_barrel"),ptbins,[&](){return truePositivesBarrel;});
    ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives_barrel"),ptbins,[&](){return trueNegativesBarrel;});
    ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives_barrel"),ptbins,[&](){return falsePositivesBarrel;});
    ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives_barrel"),ptbins,[&](){return falseNegativesBarrel;});

    ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives_endcap"),ptbins,[&](){return truePositivesEndcap;});
    ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives_endcap"),ptbins,[&](){return trueNegativesEndcap;});
    ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives_endcap"),ptbins,[&](){return falsePositivesEndcap;});
    ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives_endcap"),ptbins,[&](){return falseNegativesEndcap;});


    for(size_t i = 0; i < 6; i++)
    {
        ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives_layer_%ld",i+1),ptbins,[&,i](){return truePositivesByLayer[i];});
        ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives_layer_%ld",i+1),ptbins,[&,i](){return trueNegativesByLayer[i];});
        ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives_layer_%ld",i+1),ptbins,[&,i](){return falseNegativesByLayer[i];});
        ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives_layer_%ld",i+1),ptbins,[&,i](){return falsePositivesByLayer[i];});

        ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives_barrel_layer_%ld",i+1),ptbins,[&,i](){return truePositivesByBarrelLayer[i];});
        ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives_barrel_layer_%ld",i+1),ptbins,[&,i](){return trueNegativesByBarrelLayer[i];});
        ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives_barrel_layer_%ld",i+1),ptbins,[&,i](){return falseNegativesByBarrelLayer[i];});
        ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives_barrel_layer_%ld",i+1),ptbins,[&,i](){return falsePositivesByBarrelLayer[i];});
        
        if(i < 3)
        {
            ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives_barrel_central_layer_%ld",i+1),ptbins,[&,i](){return truePositivesByBarrelCentralLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives_barrel_central_layer_%ld",i+1),ptbins,[&,i](){return trueNegativesByBarrelCentralLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives_barrel_central_layer_%ld",i+1),ptbins,[&,i](){return falseNegativesByBarrelCentralLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives_barrel_central_layer_%ld",i+1),ptbins,[&,i](){return falsePositivesByBarrelCentralLayer[i];});

            ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives_barrel_tilted_layer_%ld",i+1),ptbins,[&,i](){return truePositivesByBarrelTiltedLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives_barrel_tilted_layer_%ld",i+1),ptbins,[&,i](){return trueNegativesByBarrelTiltedLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives_barrel_tilted_layer_%ld",i+1),ptbins,[&,i](){return falseNegativesByBarrelTiltedLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives_barrel_tilted_layer_%ld",i+1),ptbins,[&,i](){return falsePositivesByBarrelTiltedLayer[i];});

            ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives_barrel_tighter_tilted_layer_%ld",i+1),ptbins,[&,i](){return truePositivesByBarrelTighterTiltedLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives_barrel_tighter_tilted_layer_%ld",i+1),ptbins,[&,i](){return trueNegativesByBarrelTighterTiltedLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives_barrel_tighter_tilted_layer_%ld",i+1),ptbins,[&,i](){return falseNegativesByBarrelTighterTiltedLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives_barrel_tighter_tilted_layer_%ld",i+1),ptbins,[&,i](){return falsePositivesByBarrelTighterTiltedLayer[i];});

            ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives_barrel_looser_tilted_layer_%ld",i+1),ptbins,[&,i](){return truePositivesByBarrelLooserTiltedLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives_barrel_looser_tilted_layer_%ld",i+1),ptbins,[&,i](){return trueNegativesByBarrelLooserTiltedLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives_barrel_looser_tilted_layer_%ld",i+1),ptbins,[&,i](){return falseNegativesByBarrelLooserTiltedLayer[i];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives_barrel_looser_tilted_layer_%ld",i+1),ptbins,[&,i](){return falsePositivesByBarrelLooserTiltedLayer[i];});
        }

        ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives_endcap_layer_%ld",i+1),ptbins,[&,i](){return truePositivesByEndcapLayer[i];});
        ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives_endcap_layer_%ld",i+1),ptbins,[&,i](){return trueNegativesByEndcapLayer[i];});
        ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives_endcap_layer_%ld",i+1),ptbins,[&,i](){return falseNegativesByEndcapLayer[i];});
        ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives_endcap_layer_%ld",i+1),ptbins,[&,i](){return falsePositivesByEndcapLayer[i];});
        
        for(size_t j = 0; j < 15; j++)
        {
            ana.histograms.addVecHistogram(TString::Format("md_charge_true_positives_endcap_layer_%ld_ring_%ld",i+1,j+1),ptbins,[&,i,j](){return truePositivesByEndcapLayerRing[i][j];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_false_positives_endcap_layer_%ld_ring_%ld",i+1,j+1),ptbins,[&,i,j](){return falsePositivesByEndcapLayerRing[i][j];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_true_negatives_endcap_layer_%ld_ring_%ld",i+1,j+1),ptbins,[&,i,j](){return trueNegativesByEndcapLayerRing[i][j];});
            ana.histograms.addVecHistogram(TString::Format("md_charge_false_negatives_endcap_layer_%ld_ring_%ld",i+1,j+1),ptbins,[&,i,j](){return falseNegativesByEndcapLayerRing[i][j];});
        }
    }
}

void StudyChargeClassification::resetVariables()
{
    
    truePositives.clear();
    trueNegatives.clear();
    falsePositives.clear();
    falseNegatives.clear();

    truePositivesBarrel.clear();
    falsePositivesBarrel.clear();
    trueNegativesBarrel.clear();
    falseNegativesBarrel.clear();

    truePositivesEndcap.clear();
    falsePositivesEndcap.clear();
    trueNegativesEndcap.clear();
    falseNegativesEndcap.clear();

    truePositivesByLayer.clear();
    falsePositivesByLayer.clear();
    trueNegativesByLayer.clear();
    falseNegativesByLayer.clear();

    truePositivesByBarrelLayer.clear();
    falsePositivesByBarrelLayer.clear();
    trueNegativesByBarrelLayer.clear();
    falseNegativesByBarrelLayer.clear();

    truePositivesByBarrelCentralLayer.clear();
    falsePositivesByBarrelCentralLayer.clear();
    trueNegativesByBarrelCentralLayer.clear();
    falseNegativesByBarrelCentralLayer.clear();

    truePositivesByBarrelTiltedLayer.clear();
    falsePositivesByBarrelTiltedLayer.clear();
    trueNegativesByBarrelTiltedLayer.clear();
    falseNegativesByBarrelTiltedLayer.clear();

    truePositivesByBarrelTighterTiltedLayer.clear();
    falsePositivesByBarrelTighterTiltedLayer.clear();
    trueNegativesByBarrelTighterTiltedLayer.clear();
    falseNegativesByBarrelTighterTiltedLayer.clear();

    truePositivesByBarrelLooserTiltedLayer.clear();
    falsePositivesByBarrelLooserTiltedLayer.clear();
    trueNegativesByBarrelLooserTiltedLayer.clear();
    falseNegativesByBarrelLooserTiltedLayer.clear();

    truePositivesByEndcapLayer.clear();
    falsePositivesByEndcapLayer.clear();
    trueNegativesByEndcapLayer.clear();
    falseNegativesByEndcapLayer.clear();

    truePositivesByEndcapLayerRing.clear();
    falsePositivesByEndcapLayerRing.clear();
    trueNegativesByEndcapLayerRing.clear();
    falseNegativesByEndcapLayerRing.clear();

    trackPt.clear();

    //fill the small vectors inside the big ones
    for(size_t i = 1; i<= 6; i++)
    {
        truePositivesByLayer.push_back(std::vector<float>());
        trueNegativesByLayer.push_back(std::vector<float>());
        falsePositivesByLayer.push_back(std::vector<float>());
        falseNegativesByLayer.push_back(std::vector<float>());

        truePositivesByBarrelLayer.push_back(std::vector<float>());
        falsePositivesByBarrelLayer.push_back(std::vector<float>());
        trueNegativesByBarrelLayer.push_back(std::vector<float>());
        falseNegativesByBarrelLayer.push_back(std::vector<float>());

        if(i<=3)
        {
            truePositivesByBarrelCentralLayer.push_back(std::vector<float>());
            falsePositivesByBarrelCentralLayer.push_back(std::vector<float>());
            trueNegativesByBarrelCentralLayer.push_back(std::vector<float>());
            falseNegativesByBarrelCentralLayer.push_back(std::vector<float>());

            truePositivesByBarrelTiltedLayer.push_back(std::vector<float>());
            falsePositivesByBarrelTiltedLayer.push_back(std::vector<float>());
            trueNegativesByBarrelTiltedLayer.push_back(std::vector<float>());
            falseNegativesByBarrelTiltedLayer.push_back(std::vector<float>());

            truePositivesByBarrelTighterTiltedLayer.push_back(std::vector<float>());
            falsePositivesByBarrelTighterTiltedLayer.push_back(std::vector<float>());
            trueNegativesByBarrelTighterTiltedLayer.push_back(std::vector<float>());
            falseNegativesByBarrelTighterTiltedLayer.push_back(std::vector<float>());

            truePositivesByBarrelLooserTiltedLayer.push_back(std::vector<float>());
            falsePositivesByBarrelLooserTiltedLayer.push_back(std::vector<float>());
            trueNegativesByBarrelLooserTiltedLayer.push_back(std::vector<float>());
            falseNegativesByBarrelLooserTiltedLayer.push_back(std::vector<float>()); 
        }

        truePositivesByEndcapLayer.push_back(std::vector<float>());
        falsePositivesByEndcapLayer.push_back(std::vector<float>());
        trueNegativesByEndcapLayer.push_back(std::vector<float>());
        falseNegativesByEndcapLayer.push_back(std::vector<float>());

        truePositivesByEndcapLayerRing.push_back(std::vector<std::vector<float>>());
        falsePositivesByEndcapLayerRing.push_back(std::vector<std::vector<float>>());
        trueNegativesByEndcapLayerRing.push_back(std::vector<std::vector<float>>());
        falseNegativesByEndcapLayerRing.push_back(std::vector<std::vector<float>>());

        for(size_t j = 1; j<= 15; j++)
        {
            truePositivesByEndcapLayerRing.back().push_back(std::vector<float>());
            falsePositivesByEndcapLayerRing.back().push_back(std::vector<float>());
            trueNegativesByEndcapLayerRing.back().push_back(std::vector<float>());
            falseNegativesByEndcapLayerRing.back().push_back(std::vector<float>());
        }
    }
}

void StudyChargeClassification::doStudy(SDL::Event &event, std::vector<std::tuple<unsigned int, SDL::Event*>> simtrkevents)
{
    resetVariables();

    for(auto& matchedTrack:simtrkevents)
    {
        std::vector<SDL::Module*> moduleList = std::get<1>(matchedTrack)->getLowerModulePtrs();
        unsigned int& isimtrk = std::get<0>(matchedTrack);
        float simPt = std::min((double) trk.sim_pt()[isimtrk], 49.999);
        int simCharge = trk.sim_q()[isimtrk];
        trackPt.push_back(simPt);

        for(auto& module:moduleList)
        {
            //get the mini-doublets that correspond to this track
            std::vector<SDL::MiniDoublet*> matchedMDs = module->getMiniDoubletPtrs();

            for(auto& md:matchedMDs)
            {
                float dPhiChange = md->getDeltaPhiChange(); 
                //SPECULATION : Negative delta phi change = positive charge
                int charge = -(int)(dPhiChange/std::abs(dPhiChange));
                if(simCharge == 1 and charge == 1)
                {
                    truePositives.push_back(simPt);
                    truePositivesByLayer.at(module->layer()-1).push_back(simPt);
                    if(module->subdet() == SDL::Module::Barrel)
                    {
                        truePositivesBarrel.push_back(simPt);
                        truePositivesByBarrelLayer.at(module->layer()-1).push_back(simPt);
                        if(module->side() == SDL::Module::Center and module->layer() <= 3)
                        {
                            truePositivesByBarrelCentralLayer.at(module->layer()-1).push_back(simPt);
                        }
                        else if(module->layer() <= 3)
                        {
                            truePositivesByBarrelTiltedLayer.at(module->layer()-1).push_back(simPt);
                            if(SDL::MiniDoublet::isNormalTiltedModules(module))
                            {
                                truePositivesByBarrelTighterTiltedLayer.at(module->layer()-1).push_back(simPt);
                            }
                            else
                            {
                                truePositivesByBarrelLooserTiltedLayer.at(module->layer()-1).push_back(simPt);
                            }
                        }
                    }
                    else
                    {
                        truePositivesEndcap.push_back(simPt);
                        truePositivesByEndcapLayer.at(module->layer()-1).push_back(simPt);
                        truePositivesByEndcapLayerRing[module->layer()-1][module->ring()-1].push_back(simPt);
                    }
                }
                else if(simCharge == -1 and charge == -1)
                {
                    trueNegatives.push_back(simPt);
                    trueNegativesByLayer.at(module->layer()-1).push_back(simPt);
                    if(module->subdet() == SDL::Module::Barrel)
                    {
                        trueNegativesBarrel.push_back(simPt);
                        trueNegativesByBarrelLayer.at(module->layer()-1).push_back(simPt);

                        if(module->side() == SDL::Module::Center and module->layer() <= 3)
                        {
                            trueNegativesByBarrelCentralLayer.at(module->layer()-1).push_back(simPt);
                        }
                        else if(module->layer() <= 3)
                        {
                            trueNegativesByBarrelTiltedLayer.at(module->layer()-1).push_back(simPt);
                            if(SDL::MiniDoublet::isNormalTiltedModules(module))
                            {
                                trueNegativesByBarrelTighterTiltedLayer.at(module->layer()-1).push_back(simPt);
                            }
                            else
                            {
                                trueNegativesByBarrelLooserTiltedLayer.at(module->layer()-1).push_back(simPt);
                            }
                        }

                    }
                    else
                    {
                        trueNegativesEndcap.push_back(simPt);
                        trueNegativesByEndcapLayer.at(module->layer()-1).push_back(simPt);
                        trueNegativesByEndcapLayerRing[module->layer()-1][module->ring()-1].push_back(simPt);
                    }
                }
                
                else if(simCharge == 1 and charge == -1) //false negative
                {
                    falseNegatives.push_back(simPt);
                    falseNegativesByLayer.at(module->layer()-1).push_back(simPt);
                    if(module->subdet() == SDL::Module::Barrel)
                    {
                        falseNegativesBarrel.push_back(simPt);
                        falseNegativesByBarrelLayer.at(module->layer()-1).push_back(simPt);

                        if(module->side() == SDL::Module::Center and module->layer() <= 3)
                        {
                            falseNegativesByBarrelCentralLayer.at(module->layer()-1).push_back(simPt);
                        }
                        else if(module->layer() <= 3)
                        {
                            falseNegativesByBarrelTiltedLayer.at(module->layer()-1).push_back(simPt);
                            if(SDL::MiniDoublet::isNormalTiltedModules(module))
                            {
                                falseNegativesByBarrelTighterTiltedLayer.at(module->layer()-1).push_back(simPt);
                            }
                            else
                            {
                                falseNegativesByBarrelLooserTiltedLayer.at(module->layer()-1).push_back(simPt);
                            }
                        }
                    }
                    else
                    {
                        falseNegativesEndcap.push_back(simPt);
                        falseNegativesByEndcapLayer.at(module->layer()-1).push_back(simPt);
                        falseNegativesByEndcapLayerRing[module->layer()-1][module->ring()-1].push_back(simPt);
                    }

                }
                else if(simCharge == -1 and charge == 1) //false positive
                {
                    falsePositives.push_back(simPt);
                    falsePositivesByLayer.at(module->layer()-1).push_back(simPt);
                    if(module->subdet() == SDL::Module::Barrel)
                    {
                        falsePositivesBarrel.push_back(simPt);
                        falsePositivesByBarrelLayer.at(module->layer()-1).push_back(simPt);
                        
                        if(module->side() == SDL::Module::Center and module->layer() <= 3)
                        {
                            falsePositivesByBarrelCentralLayer.at(module->layer()-1).push_back(simPt);
                        }
                        else if(module->layer() <= 3)
                        {
                            falsePositivesByBarrelTiltedLayer.at(module->layer()-1).push_back(simPt);
                            if(SDL::MiniDoublet::isNormalTiltedModules(module))
                            {
                                falsePositivesByBarrelTighterTiltedLayer.at(module->layer()-1).push_back(simPt);
                            }
                            else
                            {
                                falsePositivesByBarrelLooserTiltedLayer.at(module->layer()-1).push_back(simPt);
                            }
                        }
                    }
                    else
                    {
                        falsePositivesEndcap.push_back(simPt);
                        falsePositivesByEndcapLayer.at(module->layer()-1).push_back(simPt);
                        falsePositivesByEndcapLayerRing[module->layer()-1][module->ring()-1].push_back(simPt);
                    }

                }

            }
        }
    }
}
