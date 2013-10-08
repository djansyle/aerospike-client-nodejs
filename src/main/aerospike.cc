/*******************************************************************************
 * Copyright 2013 Aerospike Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy 
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

#include <node.h>
#include "client.h"

using namespace v8;

/*******************************************************************************
 *  FUNCTIONS
 ******************************************************************************/

/**
 *	Connect to an aerospike cluster specified by the config.
 *
 *		aerospike.connect(config);
 *
 */
Handle<Value> Connect(const Arguments& args)
{
	HandleScope scope;
	return scope.Close(AerospikeClient::NewInstance(args));
}

/**
 *	Aerospike key.
 *
 *		aerospike.key(namespace, set, value);
 *
 */
Handle<Value> Key(const Arguments& args)
{
	HandleScope scope;

	if ( args.Length() == 3 ) {
		Local<Object> key = Object::New();
		key->Set(String::NewSymbol("ns"), args[0]);
		key->Set(String::NewSymbol("set"), args[1]);
		key->Set(String::NewSymbol("value"), args[2]);
		return scope.Close(key);
	}

	return scope.Close(Undefined());
}


/*
 * Error Codes in Aerospike C Client exposed to Nodejs Client
 */ 
Handle<Object> Error_Codes()
{
	HandleScope scope;
	Handle<Object> obj = Object::New();
	//Success
	obj->Set(String::NewSymbol("AEROSPIKE_OK"), Integer::New(0));
	//Generic Error
	obj->Set(String::NewSymbol("AEROSPIKE_ERR"), Integer::New(100));
	//Client API usage
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_CLIENT"), Integer::New(200));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_PARAM"), Integer::New(201));
	// Cluster Discovery and Connection
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_CLUSTER"), Integer::New(300));
	//Incomplete Requests
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_TIMEOUT"), Integer::New(400));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_THROTTLED"), Integer::New(401));
	//Competed Requests
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_SERVER"), Integer::New(500));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_REQUEST_INVALID"), Integer::New(501));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_NAMESPACE_NOT_FOUND"), Integer::New(502));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_SERVER_FULL"), Integer::New(503));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_CLUSTER_CHANGE"), Integer::New(504));
	// Record Specific
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_RECORD"), Integer::New(600));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_RECORD_BUSY"), Integer::New(601));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_RECORD_NOT_FOUND"), Integer::New(602));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_RECORD_EXISTS"), Integer::New(603));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_RECORD_GENERATION"), Integer::New(604));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_RECORD_TOO_BIG"), Integer::New(605));
	obj->Set(String::NewSymbol("AEROSPIKE_ERR_BIN_INCOMPATIBLE_TYPE"), Integer::New(606));
	
	
	return scope.Close(obj);
}
		

/**
 *	aerospike object.
 */
void Aerospike(Handle<Object> exports, Handle<Object> module)
{
	AerospikeClient::Init();

	exports->Set(String::NewSymbol("connect"), FunctionTemplate::New(Connect)->GetFunction());
	exports->Set(String::NewSymbol("key"), FunctionTemplate::New(Key)->GetFunction());
	exports->Set(String::NewSymbol("Status"), Error_Codes());
}

NODE_MODULE(aerospike, Aerospike)
