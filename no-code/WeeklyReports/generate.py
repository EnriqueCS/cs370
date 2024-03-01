import datetime
import os

def create_md_files(start_offset=-5, num_weeks=12):
    today = datetime.date.today() + datetime.timedelta(days=start_offset)

    for week in range(num_weeks):
        start_date = today + datetime.timedelta(weeks=week)
        end_date = start_date + datetime.timedelta(weeks=1) - datetime.timedelta(days=1)

        # Format filename with the start month of each week as a prefix
        file_name = f"{start_date.month:02d}Report{start_date.day:02d}-{end_date.day:02d}.md"

        with open(file_name, 'w') as file:
            file.write(f"# Report for Week {week+1} ({start_date.strftime('%Y-%m-%d')} - {end_date.strftime('%Y-%m-%d')})\n\n")

    print(f"{num_weeks} Markdown files created.")

create_md_files()