from flask import Flask, render_template, request, redirect, url_for, flash, send_file, send_file
import json
import os
import subprocess
import time

app = Flask(__name__)
app.secret_key = "5g-handover-analyzer"

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

DATA_DIR = os.path.join(BASE_DIR, "data")
OUTPUT_DIR = os.path.join(BASE_DIR, "output")

CSV_FILE = os.path.join(DATA_DIR, "handover_data.csv")
JSON_FILE = os.path.join(OUTPUT_DIR, "handover_report.json")

ANALYZER = os.path.join(BASE_DIR, "handover_analyzer")





@app.route("/")
def dashboard():

    if not os.path.exists(JSON_FILE):
        return "No analysis result found. Upload a CSV file first."

    try:
        with open(JSON_FILE, "r") as file:
            data = json.load(file)

    except Exception as e:
        return f"Error reading analysis result: {e}"

    return render_template("index.html", data=data)


@app.route("/upload", methods=["POST"])
def upload():

    if "csv_file" not in request.files:
        flash("No CSV file selected.")
        return redirect(url_for("dashboard"))

    file = request.files["csv_file"]

    if file.filename == "":
        flash("No CSV file selected.")
        return redirect(url_for("dashboard"))

    if not file.filename.lower().endswith(".csv"):
        flash("Please upload a CSV file.")
        return redirect(url_for("dashboard"))

    os.makedirs(DATA_DIR, exist_ok=True)
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    try:
        # Save uploaded CSV
        file.save(CSV_FILE)

        print("\n=====================================")
        print("CSV UPLOAD")
        print("=====================================")
        print("Uploaded file :", file.filename)
        print("Saved as      :", CSV_FILE)

        # Remove old report so we can verify that a new report is created
        if os.path.exists(JSON_FILE):
            os.remove(JSON_FILE)

        # Run C++ analyzer
        result = subprocess.run(
            [ANALYZER],
            cwd=BASE_DIR,
            capture_output=True,
            text=True
        )

        print("\n========== C++ OUTPUT ==========")
        print(result.stdout)

        if result.stderr:
            print("\n========== C++ ERROR ==========")
            print(result.stderr)

        # Check C++ execution
        if result.returncode != 0:
            flash(
                "C++ analyzer failed. Check the Flask terminal for the error."
            )
            return redirect(url_for("dashboard"))

        # Check whether JSON report was generated
        if not os.path.exists(JSON_FILE):
            flash(
                "Analyzer completed but no JSON report was generated."
            )
            return redirect(url_for("dashboard"))

        # Check that JSON contains valid data
        with open(JSON_FILE, "r") as file:
            json.load(file)

        flash(
            f"Successfully analyzed {file.filename if False else 'uploaded CSV'}."
        )

    except Exception as e:
        print("Upload error:", e)
        flash(f"Error: {e}")

    return redirect(url_for("dashboard"))


@app.route("/download/csv")
def download_csv():
    return send_file(
        os.path.join(OUTPUT_DIR, "handover_report.csv"),
        as_attachment=True,
        download_name="handover_report.csv"
    )


@app.route("/download/json")
def download_json():
    return send_file(
        os.path.join(OUTPUT_DIR, "handover_report.json"),
        as_attachment=True,
        download_name="handover_report.json"
    )


if __name__ == "__main__":
    print("=====================================")
    print("  5G HANDOVER ANALYZER WEB SERVER")
    print("=====================================")
    print("Dashboard: http://127.0.0.1:5000")
    print("=====================================")

    app.run(
        host="0.0.0.0",
        port=5000,
        debug=True
    )
