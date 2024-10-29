Email Generator

The Email Generator creates personalized emails using a template and a JSON data file, simplifying bulk email customization for newsletters and notifications.

Features
- Template Processing: Custom formatting for emails.
- JSON Integration: Automatically fills templates with data.
- Custom Outputs: Tailored emails based on user information.

Getting Started

Clone the repository:
git clone https://github.com/your-username/email-generator.git
cd email-generator

Usage
Create a template file with placeholders (e.g., `#name#`) corresponding to keys in a JSON file.

Example Template (`template.txt`:

Good day, #name#! We will respond within #XX# hours. Contact #phone_number# for immediate assistance. 

Sincerely,  
#signature#


Example JSON (`data.json`):

{
  "name": "John Doe",
  "XX": "24",
  "phone_number": "123-456-7890",
  "signature": "Jane Smith"
}


Run the Generator

./email_generator template.txt data.json
