#ifndef __ERRORCODE_H__
#define __ERRORCODE_H__

#define LM_NOERROR				 0  /** The was no error.*/
#define	LM_NOCONFFILE			-1	/** Can't find license file */
#define LM_BADFILE				-2	/** License file corrupted */
#define LM_NOSERVER	  			-3	/** Cannot connect to a license server */
#define LM_MAXUSERS	  			-4	/** Maximum number of users reached */
#define LM_NOFEATURE 			-5	/** No such feature exists */
#define LM_NOSERVICE			-6	/** No TCP/IP service  */
#define LM_NOSOCKET				-7	/** No socket to talk to server on */
#define LM_BADCODE				-8	/** Bad encryption code */
#define	LM_NOTTHISHOST			-9	/** Hostid doesn't match license */
#define	LM_LONGGONE				-10	/** Software Expired */
#define	LM_BADDATE				-11	/** Bad date in license file */
#define	LM_BADCOMM				-12	/** Bad return from server */
#define LM_NO_SERVER_IN_FILE	-13  /** No servers specified in license file */
#define LM_BADHOST				-14	/** Bad SERVER hostname in license file */
#define LM_CANTCONNECT			-15	/** Cannot connect to server */
#define LM_CANTREAD				-16	/** Cannot read from server */
#define LM_CANTWRITE			-17	/** Cannot write to server */
#define LM_NOSERVSUPP			-18	/** Server does not support this feature */
#define LM_SELECTERR			-19	/* Error in select system call */
#define LM_SERVBUSY				-20	/** Application server "busy" (connecting) */
#define LM_OLDVER				-21	/** Config file doesn't support this version */
#define LM_CHECKINBAD	 		-22	/** Feature checkin failed at daemon end */
#define LM_BUSYNEWSERV	 		-23	/** Server busy/new server connecting */
#define LM_USERSQUEUED	 		-24	/** Users already in queue for this feature */
#define	LM_SERVLONGGONE	 		-25	/** Version not supported at server end */
#define	LM_TOOMANY	 			-26	/** Request for more licenses than supported */
#define LM_CANTREADKMEM	 		-27	/** Cannot read /dev/kmem */
#define LM_CANTFINDETHER 		-29	/** Cannot find ethernet device */
#define LM_NOREADLIC	 		-30	/** Cannot read license file */
#define	LM_TOOEARLY				-31	/** Start date for feature not reached */
#define	LM_NOSUCHATTR	 		-32	/** No such attr*/
#define	LM_BADHANDSHAKE	 		-33	/** Bad encryption handshake with server */
#define LM_CLOCKBAD	 			-34	/** Clock difference too large between client/server */
#define LM_FEATQUEUE	 		-35	/** We are in the queue for this feature */
#define LM_FEATCORRUPT	 		-36	/** Feature database corrupted in daemon */
#define LM_BADFEATPARAM	 		-37	/** dup_select mismatch for this feature */
#define LM_FEATEXCLUDE	 		-38	/** User/host on EXCLUDE list for feature */
#define LM_FEATNOTINCLUDE		-39	/** User/host not in INCLUDE list for feature */
#define LM_CANTMALLOC	 		-40	/** Cannot allocate dynamic memory */
#define LM_NEVERCHECKOUT 		-41	/** Feature never checked out */
#define LM_BADPARAM		 		-42	/** Invalid parameter */
#define LM_NOKEYDATA	 		-43	/** No license key data */
#define LM_BADKEYDATA	 		-44	/** Invalid license key data */
#define LM_FUNCNOTAVAIL	 		-45	/** LicManager function not available */
#define LM_DEMOKIT	     		-46	/** LicManager software is demonstration version */
#define LM_NOCLOCKCHECK	 		-47	/** Clock check not available in daemon */
#define LM_BADPLATFORM	 		-48	/** LicManager platform not enabled */
#define LM_DATE_TOOBIG	 		-49	/** Date too late for binary format */
#define LM_EXPIREDKEYS	 		-50	/** License key data has expired */
#define LM_NOLICMANAGERINIT	 	-51	/** LicManager not initialized */
#define LM_NOSERVRESP	 		-52	/** Server did not respond to message */
#define LM_CHECKOUTFILTERED 	-53	/** Request rejected by vendor-defined filter */
#define LM_SOCKETFAIL	 		-57	/** socket() call failed */
#define LM_SETSOCKFAIL	 		-58	/** setsockopt() failed */
#define LM_BADCHECKSUM	 		-59	/** message checksum failure */
#define LM_SERVBADCHECKSUM 		-60	/** server message checksum failure */
#define LM_SERVNOREADLIC 		-61	/** Cannot read license file from server */
#define LM_NONETWORK	 		-62	/** Network software (tcp/ip) not available */
#define LM_NOTLICADMIN	 		-63	/** Not a license administrator */
#define LM_REMOVETOOSOON 		-64	/** lmremove request too soon */
#define LM_LIBRARYMISMATCH 		-66	/** LicManager include file/library mismatch */
#define LM_LOCALFILTER   		-73	/** Local checkout filter requested request */
#define LM_ENDPATH	     		-74	/** Attempt to read beyond the end of LF path */
#define LM_INTERNAL_ERROR		-76	/** Internal LicManager error -- Please report */
#define LM_BAD_VERSION   		-77	/** Invliad version */
#define LM_NOADMINAPI    		-78	/** LicManager API functions not available */
#define LM_NOFILEOPS     		-79 /** LicManager internal error -79 */
#define LM_NODATAFILE    		-80 /** LicManager internal error -80 */
#define LM_NOFILEVSEND   		-81 /** LicManager internal error -81 */
#define LM_SERVOLDVER	 		-83	/** Server LicManager version older than client's */
#define LM_NOSERVCAP	 		-85	/** Server doesn't support this request */
#define LM_OBJECTUSED	 		-86	/** This license object already in use*/
#define LM_MAXLIMIT	     		-87	/** Checkout exceeds MAX specified in options file */
#define LM_BADSYSDATE	 		-88	/** System clock has been set back */
#define LM_PLATNOTLIC	 		-89	/** This platform not authorized by license */
#define LM_FUTURE_FILE	 		-90	/** "Future license file format or misspelling in license file" */
#define LM_SERVER_REMOVED  		-92	/** "Server removed during reread, or server hostid mismatch with license" */
#define LM_POOL 				-93	/** "This feature is available in a different license pool" */
#define LM_LGEN_VER 			-94	/** "Attempt to generate license with incompatible attributes" */
#define LM_NOT_THIS_HOST 		-95 /** "Network connect to THIS_HOST failed" */
#define LM_HOSTDOWN 			-96 /** "Server node is down or not responding" */
#define LM_VENDOR_DOWN 			-97 /** "The desired vendor daemon is down" */
#define LM_CANT_DECIMAL 		-98 /** "The FEATURE line can't be converted to decimal format" */
#define LM_BADDECFILE 			-99  /** "The decimal format license is typed incorrectly" */
#define LM_REMOVE_LINGER 		-100 /** "Cannot remove a lingering license" */
#define LM_RESVFOROTHERS 		-101 /** "All licenses are reserved for others" */
#define LM_TSOK_ERR 			-103 /** Terminal Server remote client not allowed */
#define LM_SERVER_MAXED_OUT 	-106 /** "License server out of network connections" */
#define LM_NORESLINK 			-111 /** "Windows Resource file, not linked" */
#define LM_LICLOCK2CKOUT 		-113 /** "2 LIC checkouts attempted" */
#define LM_SIGN_REQ 			-114 /**"SIGN= attribute required, but missing from license"*/
#define LM_PUBKEY_ERR 			-115 /** "Error in Public Key package" */
#define LM_NOCROSUPPORT 		-116 /** "CRO not supported for this platform" */
#define LM_MUST_BE_LOCAL 		-119 /** "lmdown and lmreread must be run on license server node" */
#define LM_CANT_CHECKOUT_JUST_PACKAGE	-125 /** Error when trying to just checkout a PACKAGE(BUNDLE) */
#define LM_COMPOSITEID_INIT_ERR 		-126 /** "Composite Hostid not initialized" */
#define LM_COMPOSITEID_ITEM_ERR 		-127 /** "An item needed for Composite Hostid missing or invalid" */
#define LM_NULLPOINTER			-129 /** A null pointer was detected.*/
#define LM_BADHANDLE			-130 /** A bad handle was used.*/
#define LM_EMPTYSTRING			-131 /** An emptstring was detected. */
#define LM_BADMEMORYACCESS		-132 /** Tried to asscess memory that we shouldn't have. */
#define LM_NOTSUPPORTED			-133 /** Operation is not supported yet.*/
#define LM_NULLJOBHANDLE		-134 /** The job handle was NULL. */
#define LM_EVENTLOG_INIT_ERR	-135 /** Error enabling event log */
#define LM_EVENTLOG_DISABLED	-136 /** Event logging is disabled */
#define LM_EVENTLOG_WRITE_ERR	-137 /** Error writing to event log */



//extern struct tErrorString g_sErrorString;
#endif