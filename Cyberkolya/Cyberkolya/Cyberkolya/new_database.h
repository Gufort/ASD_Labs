#ifndef NEW_DATABASE_H
#define NEW_DATABASE_H

#include "abstract_database.h"
#include <unordered_map>
#include <vector>

class NewDatabase: public AbstractDatabase {
private:
	std::unordered_map<int, std::unordered_map<int, Post>> _posts; // [ownerID][ID] -> Post 
	std::unordered_map<int, User> _users; // [ID] -> User

public:
	const User& get_user(int id) override {
		auto current = _users.find(id);
		if (current != _users.end())
			return current->second;
		else throw DatabaseException("User not found!");
	}

	const Post& get_post(int ownerId, int postId) override {
		auto owner = _posts.find(ownerId);
		if (owner != _posts.end()) {
			auto post = owner->second.find(postId);
			if (post != owner->second.end())
				return post->second;
		}
		else throw DatabaseException("Post not found!");
	}

	void insert_user(const User& user) override {
		if (_users.count(user.Id) != 1)
			_users[user.Id] = user;
	}

	void insert_post(const Post& post) override {
		throw DatabaseException("!!!!!!!!!!");
	}

	void delete_post(int ownerId, int postId) override {
		throw DatabaseException("!!!!!!!!!!");
	}
	
	void like_post(int ownerId, int postId) override {
		throw DatabaseException("!!!!!!!!!!");
	}

	void unlike_post(int ownerId, int postId) override {
		throw DatabaseException("!!!!!!!!!!");
	}

	void repost_post(int ownerId, int postId) override {
		throw DatabaseException("!!!!!!!!!!");
	}

	std::vector<Post> top_k_post_by_likes(int k, int ownerId, int dateBegin, int dateEnd) override {
		throw DatabaseException("!!!!!!!!!!");
	}

	std::vector<Post> top_k_post_by_reposts(int k, int ownerId, int dateBegin, int dateEnd) override {
		throw DatabaseException("!!!!!!!!!!");
	}

	std::vector<UserWithLikes> top_k_authors_by_likes(int k, int ownerId, int dateBegin, int dateEnd) override {
		throw DatabaseException("!!!!!!!!!!");
	}

	std::vector<UserWithReposts> top_k_authors_by_reports(int k, int ownerId, int dateBegin, int dateEnd) override {
		throw DatabaseException("!!!!!!!!!!");
	}
};

#endif // !NEW_DATABASE_H
