//thrift -r -gen cpp rtm.thrift

service Serv{
     bool auth(1: i32 pid, 2: i64 uid, 3: string token, 4: string version),
     void send_broadcast_group_msg(1: i64 group_id, 2: i64 mid, 3: i8 mtype, 4: string message),
     void bye(),
     void add_variable(1: map<string, string> kv),
}
