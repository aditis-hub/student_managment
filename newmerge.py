import pandas as pd
import os

# Load the first CSV file
file1 = "student.csv"
file2 = "marks.csv"
output_file = "merged_students.csv"

# Read the CSV files
df1 = pd.read_csv(file1)
df2 = pd.read_csv(file2)

# Merge the files (row-wise)
merged_df = pd.concat([df1, df2], ignore_index=True)

# Save the merged file
merged_df.to_csv(output_file, index=False)

print(f"Files merged successfully into {output_file}")

os.system("student_database.exe")