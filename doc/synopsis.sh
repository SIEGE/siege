INDIR=../include/siege
EXT=h

OUTNAME=output

TMPDIR=tmp

##########

INDIR=`echo "$INDIR" | sed 's/\/$//'`

INLEN=`echo "$INDIR" | awk '{ print length }'`
let START=$INLEN + 2 > /dev/null

HEADERS=`find $INDIR | grep "\.$EXT$" | xargs`

#echo "Files: $FILES"

mkdir -p $TMPDIR

echo 'Parsing...'
TMPFILES=''
for header in $HEADERS; do
	tmpfile=`echo $header | cut -c"$START-"`
	tmpfile=$TMPDIR/$tmpfile.syn
	tmpdir=`echo "$tmpfile" | sed 's/\/[^\/]*$//'`
	echo "$header => $tmpfile"
	mkdir -p "$tmpdir"
	python synopsis.py c_sg --output="$tmpfile" $header
	TMPFILES=`echo $TMPFILES $tmpfile`
done
echo 'Linking...'
python synopsis.py link --output=$TMPDIR/$OUTNAME.link $TMPFILES
echo 'Generating HTML...'
python synopsis.py html --output=html $TMPDIR/$OUTNAME.link
#echo 'Generating Dot...'
#python synopsis.py dot --output=$TMPDIR/dot $TMPDIR/$OUTNAME.link
#echo 'Generating Dump...'
#python synopsis.py dump --output=$TMPDIR/dump.txt $TMPDIR/$OUTNAME.link
echo 'Done!'

