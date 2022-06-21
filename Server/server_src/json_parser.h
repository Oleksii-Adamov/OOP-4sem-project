#include <string>
#include <vector>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

#include "../../common_src/Entities/Entities.h"
#include "../../common_src/studentassignmentsessioninfo.h"
#include "../../common_src/studentassignmentsessioninfoforteacher.h"

namespace bpt = boost::property_tree;

std::string ParseToJson(const std::vector<Classroom>& classrooms) {
	std::stringstream text;
	bpt::ptree json;
	bpt::ptree array;
	// Converting classrooms in json class and put in array
	for (const Classroom& classroom : classrooms) {
		bpt::ptree element;
		element.put("classroom_id", classroom.getClassroomId());
		element.put("teacher_user_id", classroom.getTeacherUserId());
		element.put("name", classroom.getName());
		array.push_back(bpt::ptree::value_type("", element));
	}
	json.put_child("Classrooms", array);
	bpt::write_json(text, json);
	
	return text.str();
}

std::string ParseToJson(const std::vector<Assignment>& assignments) {
	std::stringstream text;
	bpt::ptree json;
	bpt::ptree array;
	// Converting classrooms in json class and put in array
	for (const Assignment& assignment : assignments) {
		bpt::ptree element;
		element.put("assignment_id", assignment.getAssignmentId());
		element.put("teacher_user_id", assignment.getTeacherUserId());
		element.put("assignment_name", assignment.getAssignmentName());
		element.put("assignment_creation_date",
								assignment.getAssignmentCreationDate());
		element.put("assignment_data", assignment.getAssignmentData());
		element.put("assignment_max_score", assignment.getAssignmentMaxScore());
		array.push_back(bpt::ptree::value_type("", element));
	}
	json.put_child("Assignments", array);
	bpt::write_json(text, json);
	
	return text.str();
}