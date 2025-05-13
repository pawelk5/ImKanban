#!/usr/bin/env python3
import argparse

parser = argparse.ArgumentParser(
        prog='generateEmbed',
        description='Generate file for embedding resources in C/C++')

parser.add_argument('sourcefile', help='source file', type=str)
parser.add_argument('destinationfile', help='destination file', type=str)
parser.add_argument('arrayname', help='array name', type=str)

parser.add_argument('--licencefile', help='licence file (optional)', type=str)


args = parser.parse_args()

def main():
    with open(args.sourcefile, 'rb') as input_file, open(args.destinationfile, 'w') as output_file:
        data = input_file.read()

        output_file.write(f"// Generated from {args.sourcefile}\n")
        if (args.licencefile):
            with open(args.licencefile, 'r') as licence_file:
                output_file.write(f"/* LICENCE:\n{licence_file.read()}\n*/\n")

        output_file.write(f"const unsigned char {args.arrayname}[] = {{\n\t")

        line_length = 0
        for i, byte in enumerate(data):
            output_file.write(f"0x{byte:02X}, ")
            line_length += 1
            if line_length >= 16:
                output_file.write("\n\t")
                line_length = 0
        
        # trick for removing last `,`
        output_file.seek(output_file.tell() - 2, 0)
        output_file.write(f"\r\n}};\n")
        output_file.write(f"const unsigned int {args.arrayname}Size = {len(data)};\n")

if __name__ == "__main__":
    main()