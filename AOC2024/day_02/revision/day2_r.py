from sys import argv as _argv

def calculate_deltas(report):
    pairs = [tuple for tuple in zip(report, report[1:])]
    return list(map(lambda tuple: tuple[0] - tuple[1], pairs))

def verify_deltas(deltas):
    all_increasing = all([(0 < delta and delta < 4) for delta in deltas])
    all_decreasing = all([(-4 < delta and delta < 0) for delta in deltas])
    return all_increasing or all_decreasing

def attempt_level_fix(report_tokens):
    for i in range(0, len(report_tokens)):
        trial_report = report_tokens.copy()
        trial_report.pop(i)
        trial_deltas = calculate_deltas(trial_report)
        if verify_deltas(trial_deltas):
            return trial_report
    return None

def safe_report_counter(file, dampener=False):
    safe_reports = 0
    for report in file:
        tokens = report.split(" ")
        tokens = list(map(int, tokens))
        deltas = calculate_deltas(tokens)

        if (verify_deltas(deltas)):
            safe_reports += 1
        elif dampener:
            if attempt_level_fix(tokens):
                safe_reports += 1
    return safe_reports

def main(file):
    f = open(file, "r")
    print(safe_report_counter(f, False))
    f.close()

if __name__== "__main__":
    if (len(_argv) != 2):
        print("Please provide an input file.")
        exit()
    main(_argv[1])
