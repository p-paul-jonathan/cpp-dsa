if [ -z "$1" ]; then
    echo "Error: No input file provided."
    exit 1
fi

argument="$1"

filename=$(basename $argument | cut -d '.' -f 1)

echo "Compiling..."
g++ $1 -o output/$filename.out
echo "Done"

echo "Running..."
echo "Output: "
output/$filename.out
echo "Done"
