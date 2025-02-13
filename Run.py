#!/usr/bin/env python3
import subprocess
import os
import sys

def compile_executables():
    """
    Compile all required C++ files.
    If you already have the executables, you can comment out this function.
    """
    files_to_compile = [
        ("Knapsack.cpp", "Knapsack"),
        ("PolygonConstruction.cpp", "PolygonConstruction"),
        ("checker.cpp", "checker"),
        ("Top250.cpp", "Top250"),
        # ("Annealing.cpp", "Annealing")  # Not used in the current chain.
    ]
    for src, exe in files_to_compile:
        print(f"Compiling {src} into {exe}...")
        result = subprocess.run(["g++", src, "-o", exe])
        if result.returncode != 0:
            print(f"Compilation failed for {src}. Exiting.")
            sys.exit(1)
    print("All files compiled successfully.\n")

def run_for_input(input_file , index):
    print(f"\n=== Processing {input_file} ===")

    # 1. Run Knapsack.cpp: (reads input_file, creates Boolean_B.txt)
    try:
        with open(input_file, "r") as f_in:
            result = subprocess.run(["./Knapsack"], stdin=f_in)
            if result.returncode != 0:
                print("Error running Knapsack.")
                return
    except Exception as e:
        print(f"Error opening {input_file} for Knapsack: {e}")
        return
    # 2. Run PolygonConstruction.cpp: (reads Boolean_B.txt, creates Edges.txt)
    if not os.path.exists("Boolean_B.txt"):
        print("Boolean_B.txt not found. Skipping this input.")
        return
    try:
        with open("Boolean_B.txt", "r") as f_in:
            result = subprocess.run(["./PolygonConstruction"], stdin=f_in)
            if result.returncode != 0:
                print("Error running PolygonConstruction.")
                return
    except Exception as e:
        print(f"Error running PolygonConstruction: {e}")
        return
    # 3. Run checker.cpp: (reads Edges.txt, creates output.txt)
    if not os.path.exists("Edges.txt"):
        print("Edges.txt not found. Skipping this input.")
        return
    try:
        with open("Edges.txt", "r") as f_in:
            # result = subprocess.run(["./checker"], stdin=f_in)
            result = subprocess.run(["./checker", "Edges.txt", input_file])
            if result.returncode != 0:
                print("Error running checker.")
                return
    except Exception as e:
        print(f"Error running checker: {e}")
        return

    # 4. Run Top250.cpp: (reads the same input file, creates top250.txt)
    try:
        with open(input_file, "r") as f_in:
            result = subprocess.run(["./Top250"], stdin=f_in)
            if result.returncode != 0:
                print("Error running Top250.")
                return
    except Exception as e:
        print(f"Error opening {input_file} for Top250: {e}")
        return

    # 5. Compare the first number in output.txt and top250.txt and print the file with the larger number.
    if not os.path.exists("output.txt") or not os.path.exists("top250.txt"):
        print("One or both expected output files (output.txt, top250.txt) were not created.")
        return

    try:
        with open("output.txt", "r") as f:
            output_contents = f.read().strip()
        with open("top250.txt", "r") as f:
            top250_contents = f.read().strip()

        output_first = float(output_contents.split()[0])
        top250_first = float(top250_contents.split()[0])
    except Exception as e:
        print(f"Error processing output files: {e}")
        return

    # Ensure the output directory exists.
    output_dir = "output"
    os.makedirs(output_dir, exist_ok=True)

    # Build the output file path, e.g., "output/output00.txt" for input00.txt
    final_output_filename = os.path.join(output_dir, f"output{index:02}.txt")

    current_max = max(output_first, top250_first)

    if output_first >= top250_first:
        print(f"output.txt has the larger (or equal) first number: {output_first} vs {top250_first}")
        print("----- Contents of output.txt -----")
        # print(output_contents)
        with open(final_output_filename, "w") as f:
            f.write(output_contents)
    else:
        print(f"top250.txt has the larger first number: {top250_first} vs {output_first}")
        print("----- Contents of top250.txt -----")
        # print(top250_contents)
        with open(final_output_filename, "w") as f:
            f.write(top250_contents)
    return current_max


def main():
    # Uncomment the next line if you need to compile the executables.
    compile_executables()
    total_sum=0
    # Process input files: input00.txt to input19.txt
    for i in range(20):
        input_filename = os.path.join("input", f"input{i:02}.txt")
        if os.path.exists(input_filename):
            total_sum+=run_for_input(input_filename , i)
        else:
            print(f"File {input_filename} does not exist. Skipping.")
        

    print(f"Sum of all the first numbers is {total_sum}")

if __name__ == '__main__':
    main()
