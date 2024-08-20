import markdown
import os

with open('__template.html', 'r') as f:
    html = ''.join(f.readlines())

for dir in os.listdir():
    if not os.path.isdir(dir):
        continue

    if dir[0] == '.':
        continue

    with open(os.path.join(dir, 'details.md'), 'r') as input_file:
        html_content = markdown.markdown(
            ''.join(input_file.readlines()), 
            extensions=['fenced_code']
        )

        with open(os.path.join(dir, 'details.html'),'w') as output_file:
            page = html.replace('__TITLE__', ' '.join(dir.split('_')))
            page = page.replace('__CONTENT__', html_content)
            output_file.write(page)