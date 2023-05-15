import subprocess
import json

def run_code(file_path):
    result = {}

    dic = {
        '.py': 'python',
        '.cpp': 'c++',
        '.java': 'java',
        '.js': 'javascript'
    }

    language = dic[file_path[file_path.rfind('.'):]]

    if language == 'python':
        command = ['python', file_path]
        result['file'] = file_path
    elif language == 'c++':
        executable = file_path.replace('.cpp', '.exe')
        compile_command = ['g++', file_path, '-o', executable]
        if subprocess.call(compile_command) != 0:
            result['status'] = 'Compilation Error'
            result['error'] = 'Failed to compile the code.'
            return result
        command = [executable]
        result['file'] = executable
    elif language == 'java':
        compile_command = ['javac', file_path]
        if subprocess.call(compile_command) != 0:
            result['status'] = 'Compilation Error'
            result['error'] = 'Failed to compile the code.'
            return result
        class_name = file_path.replace('.java', '')
        command = ['java', class_name]
        result['file'] = class_name
    elif language == 'javascript':
        command = ['node', file_path]
        result['file'] = file_path
    else:
        result['status'] = 'Error'
        result['error'] = 'Unsupported language.'
        return result

    try:
        output = subprocess.check_output(command, stderr=subprocess.STDOUT, timeout=5)
        result['status'] = 'Success'
        result['output'] = output.decode('utf-8')
    except subprocess.CalledProcessError as e:
        result['status'] = 'Success'
        result['error'] = e.output.decode('utf-8')
    except subprocess.TimeoutExpired as e:
        result['status'] = 'Success'
        result['error'] = e.output.decode('utf-8')

    return result

# Example usage


code_file = '/home/alen/Desktop/Educational/Portfolio/Java/src/Main.java'
#code_file = './example.cpp'
result = run_code(code_file)
output_file = 'result.json'

with open(output_file, 'w') as f:
    json.dump(result, f, indent=4)

print(f"Result saved to {output_file}")