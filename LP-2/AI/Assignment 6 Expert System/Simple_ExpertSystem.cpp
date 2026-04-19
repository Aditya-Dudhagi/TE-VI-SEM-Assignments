#include<iostream>
#include<algorithm>
using namespace std;

class Employee{
    int attendance,quality,teamwork, projects;
    bool deadline;
    public:
    Employee(int attendance,int quality,int teamwork,int projects,bool deadline):
    attendance(attendance),
    quality(quality),
    teamwork(teamwork),
    projects(projects),
    deadline(deadline)
    {}
    Employee():
    attendance(0),
    quality(0),
    teamwork(0),
    projects(0),
    deadline(false)
    {
        // getInput();
    }

    void getInput(int attendance,int quality,int teamwork,int projects,bool deadline){
        this->attendance=attendance;
        this->quality=quality;
        this->teamwork=teamwork;
        this->projects=projects;
        this->deadline=deadline;
    }
    void getInput(){
        cout<<"Enter attendence of employee(0-100%): ";
        cin>>attendance;

        cout<<"Enter Work Quality of employee(1-10): ";
        cin>>quality;

        cout<<"Enter Teamwork level(1-10): ";
        cin>>teamwork;

        cout<<"Enter Number of projects: ";
        cin>>projects;

        string str;
        cout<<"Deadline met(yes/no)";
        cin>>str;
        transform(str.begin(), str.end(), str.begin(), ::tolower);

        deadline=(str.find('y')!=string::npos||str.find('1')!=string::npos);  //1=yes,0=no
    }

    void displayData(){
        cout<<"Employee Information"<<endl;
        cout<<"\tAttendance: "<<attendance<<endl;
        cout<<"\tQuality: "<<quality<<endl;
        cout<<"\tTeamwork: "<<teamwork<<endl;
        cout<<"\tProjects: "<<projects<<endl;
        cout<<"\tDeadline: "<<(deadline ? "Yes" : "No") <<endl;
    }

    void evaluate(){
        if(attendance > 90 && quality > 8 && teamwork > 8 && deadline && projects >= 5) {
            cout << "Rating: Outstanding Performer\n";
            cout << "Reason: Excellent attendance, high quality work, strong teamwork and meets deadlines consistently.\n";
            cout << "Suggestion: Ready for promotion or leadership roles.\n";
        }else if(attendance > 90 && quality > 8 && teamwork > 8 && deadline) {
            cout << "Rating: Excellent\n";
            cout << "Reason: Strong performance in all key areas.\n";
            cout << "Suggestion: Maintain consistency and take more initiative.\n";
        }else if(attendance > 80 && quality > 7 && deadline) {
            cout << "Rating: Very Good\n";
            cout << "Reason: Good attendance and work quality with timely task completion.\n";
            cout << "Suggestion: Improve teamwork or leadership for higher rating.\n";
        }else if(quality > 8 && teamwork < 5) {
            cout << "Rating: Technically Strong\n";
            cout << "Reason: High work quality but poor teamwork.\n";
            cout << "Suggestion: Improve collaboration and communication skills.\n";
        }else if(projects >= 3 && quality > 6) {
            cout << "Rating: Good\n";
            cout << "Reason: Decent project contribution and satisfactory work quality.\n";
            cout << "Suggestion: Increase consistency and improve teamwork.\n";
        }else if(teamwork > 8 && quality < 5) {
            cout << "Rating: Good Team Player\n";
            cout << "Reason: Strong teamwork but low individual performance.\n";
            cout << "Suggestion: Focus on improving technical/work skills.\n";
        }else if(attendance > 85 && !deadline) {
            cout << "Rating: Irregular Performer\n";
            cout << "Reason: Good attendance but fails to meet deadlines.\n";
            cout << "Suggestion: Improve time management.\n";
        }else if(attendance > 65 && quality > 5) {
            cout << "Rating: Average\n";
            cout << "Reason: Moderate attendance and work quality.\n";
            cout << "Suggestion: Improve both consistency and productivity.\n";
        }else if(projects < 2 && quality < 5) {
            cout << "Rating: Underperformer\n";
            cout << "Reason: Low project contribution and poor quality.\n";
            cout << "Suggestion: Increase involvement and focus on skill improvement.\n";
        }else if(attendance < 60 && !deadline) {
            cout << "Rating: Poor\n";
            cout << "Reason: Low attendance and missed deadlines.\n";
            cout << "Suggestion: Improve attendance and discipline.\n";
        }else {
            cout << "Rating: Needs Improvement\n";
            cout << "Reason: Performance does not meet expected standards.\n";
            cout << "Suggestion: Work on multiple areas including quality, teamwork, and punctuality.\n";
        }
    }
};

int main(){
    cout<<endl;
    // Employee e(95,9,9,10,true);
    Employee e;
    e.displayData();
    e.evaluate();
    cout<<endl;

    e.getInput(95,9,9,10,true);
    e.displayData();
    e.evaluate();
    cout<<endl;

    e.getInput(85,8,7,13,true);
    e.displayData();
    e.evaluate();
    cout<<endl;

    e.getInput(85,8,7,13,false);
    e.displayData();
    e.evaluate();
    cout<<endl;

    e.getInput(85,5,7,13,true);
    e.displayData();
    e.evaluate();
    cout<<endl;
    cout<<endl;
    return 0;
}