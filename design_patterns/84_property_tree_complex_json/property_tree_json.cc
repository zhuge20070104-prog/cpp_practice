#include "property_tree_json.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <exception>

namespace pt = boost::property_tree;
using ptree = boost::property_tree::ptree;
using ptree_value_type = ptree::value_type;

namespace client {
    track_infos::track_infos(std::string const& file_name):
        m_file_name(file_name) {}
    

    /*
    Ptree structure
    struct ptree {
        data_type data;                         // data associated with the node
        list< pair<key_type, ptree> > children; // ordered list of named children
    };
    */
    void track_infos::load() {
        ptree tree;
        pt::read_json(m_file_name, tree);
        auto tracks = tree.get_child("tracks");

        for(auto & track: tracks) {
            auto a_track = track.second;
            
            auto traj_type = a_track.get<std::string>("trajectory_type");
            std::cout << "trajectory_type: " << traj_type << std::endl;
            auto& waypoints_t = a_track.get_child("waypoints");

            std::cout << "size of waypoints: " << waypoints_t.size() << std::endl;
            for(auto waypoint: waypoints_t) {
                if(waypoint.second.find("pose") != waypoint.second.not_found()) {
                    auto&  pose = waypoint.second.get_child("pose");
                    if(pose.find("x") != pose.not_found()) {
                        std::cout << "has pose X: " << waypoint.second.get<float>("pose.x") << std::endl;
                    }
                    if(pose.find("y") != pose.not_found()) {
                        std::cout << "has pose Y: " << waypoint.second.get<float>("pose.y") << std::endl;
                    }
                    if(pose.find("theta")!= pose.not_found()) {
                        std::cout << "has pose theta: " << waypoint.second.get<float>("pose.theta") << std::endl;
                    }
                }

                if(waypoint.second.find("direction") != waypoint.second.not_found()) {
                    std::cout << "has direction: " << waypoint.second.get<std::string>("direction") << std::endl;
                }

                if(waypoint.second.find("speed") != waypoint.second.not_found()) {
                    std::cout << "has speed: " << waypoint.second.get<float>("speed") << std::endl;
                }

                std::cout << "================================================================" << std::endl;
            }
            std::stringstream track_ss;
            pt::write_json(track_ss, track.second);
            m_tracks.push_back(track_ss.str());
        }
    }

    void track_infos::save() {
        ptree tree;
        ptree tracks;
        for(auto& track: m_tracks) {
            ptree s_tree;
            std::stringstream s_tree_ss;
            s_tree_ss << track;
            // std::cout << "A track:" << std::endl;
            // std::cout << s_tree_ss.str() << std::endl; 
            pt::read_json(s_tree_ss, s_tree);
            tracks.push_back(ptree_value_type("", s_tree));
        }

        tree.add_child("tracks", tracks);
        pt::write_json("./res.json", tree);
    }
};