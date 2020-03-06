
SAMPLETAG=$1
JOBTAG=$2
OUTPUTFILE=fulleff_${SAMPLETAG}.root

if [ -z $1 ]; then
    echo "Job tag information for the plotter is not provided"
fi

rm -rf plots_${SAMPLETAG}
rm -rf results/${SAMPLETAG}${JOBTAG}/plots_${SAMPLETAG}
python plot.py 1 results/${SAMPLETAG}${JOBTAG}/${OUTPUTFILE} ${SAMPLETAG}
python plot.py 2 results/${SAMPLETAG}${JOBTAG}/${OUTPUTFILE} ${SAMPLETAG}
python plot.py 3 results/${SAMPLETAG}${JOBTAG}/${OUTPUTFILE} ${SAMPLETAG}
python plot.py 4 results/${SAMPLETAG}${JOBTAG}/${OUTPUTFILE} ${SAMPLETAG}
cp -r plots_${SAMPLETAG}/ results/${SAMPLETAG}${JOBTAG}/plots_${SAMPLETAG}
