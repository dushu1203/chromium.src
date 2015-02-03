// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_AFFILIATION_BACKEND_H_
#define COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_AFFILIATION_BACKEND_H_

#include <map>
#include <vector>

#include "base/containers/scoped_ptr_hash_map.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "components/password_manager/core/browser/affiliation_fetcher_delegate.h"
#include "components/password_manager/core/browser/affiliation_service.h"
#include "components/password_manager/core/browser/affiliation_utils.h"

namespace base {
class Clock;
class FilePath;
class ThreadChecker;
class Time;
}  // namespace base

namespace net {
class URLRequestContextGetter;
}  // namespace net

namespace password_manager {

class AffiliationDatabase;
class AffiliationFetcher;

// The AffiliationBackend is the part of the AffiliationService that lives on a
// background thread suitable for performing blocking I/O. As most tasks require
// I/O, the backend ends up doing most of the work for the AffiliationService;
// the latter being just a thin layer that delegates most tasks to the backend.
//
// This class is not thread-safe, but it is fine to construct it on one thread
// and then transfer it to the background thread for the rest of its life.
// Initialize() must be called already on the background thread.
class AffiliationBackend : public AffiliationFetcherDelegate {
 public:
  // Constructs an instance that will use |request_context_getter| for all
  // network requests, and will rely on |time_source| to tell the current time,
  // which is expected to always be strictly greater than the NULL time.
  // Construction is very cheap, expensive steps are deferred to Initialize().
  AffiliationBackend(
      const scoped_refptr<net::URLRequestContextGetter>& request_context_getter,
      scoped_ptr<base::Clock> time_source);
  ~AffiliationBackend() override;

  // Performs the I/O-heavy part of initialization. The database to cache
  // affiliation information locally will be opened/created at |db_path|.
  void Initialize(const base::FilePath& db_path);

  // Implementations for methods of the same name in AffiliationService. They
  // are not documented here again. See affiliation_service.h for details:
  void GetAffiliations(
      const FacetURI& facet_uri,
      bool cached_only,
      const AffiliationService::ResultCallback& callback,
      const scoped_refptr<base::TaskRunner>& callback_task_runner);
  void Prefetch(const FacetURI& facet_uri, const base::Time& keep_fresh_until);
  void CancelPrefetch(const FacetURI& facet_uri,
                      const base::Time& keep_fresh_until);
  void TrimCache();

 private:
  class FacetManager;
  friend class FacetManager;

  // Collects facet URIs that require fetching and issues a network request
  // against the Affiliation API to fetch corresponding affiliation information.
  void SendNetworkRequest();

  // Gets the current time as per |clock_|. The returned time will always be
  // strictly greater than the NULL time. Used by FacetManager.
  base::Time GetCurrentTime();

  // Reads and returns the last update time of the equivalence class containing
  // |facet_uri| from the database, or, if no such equivalence class is stored,
  // returns the NULL time. Used by FacetManager.
  base::Time ReadLastUpdateTimeFromDatabase(const FacetURI& facet_uri);

  // Reads the equivalence class containing |facet_uri| from the database and
  // returns true if found; returns false otherwise. Used by FacetManager.
  bool ReadAffiliationsFromDatabase(
      const FacetURI& facet_uri,
      AffiliatedFacetsWithUpdateTime* affiliations);

  // Signals the fetching logic that there is at least one facet that needs to
  // be fetched immediately. Called by FacetManager.
  void SignalNeedNetworkRequest();

  // AffiliationFetcherDelegate:
  void OnFetchSucceeded(
      scoped_ptr<AffiliationFetcherDelegate::Result> result) override;
  void OnFetchFailed() override;
  void OnMalformedResponse() override;

  // Created in Initialize(), and ensures that all subsequent methods are called
  // on the same thread.
  scoped_ptr<base::ThreadChecker> thread_checker_;

  scoped_refptr<net::URLRequestContextGetter> request_context_getter_;

  // Will always return a Now() that is strictly greater than the NULL time.
  scoped_ptr<base::Clock> clock_;

  scoped_ptr<AffiliationDatabase> cache_;
  scoped_ptr<AffiliationFetcher> fetcher_;

  // Contains a FacetManager for each facet URI that need ongoing attention. To
  // save memory, managers are discarded as soon as they become redundant.
  base::ScopedPtrHashMap<FacetURI, FacetManager> facet_managers_;

  base::WeakPtrFactory<AffiliationBackend> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(AffiliationBackend);
};

}  // namespace password_manager

#endif  // COMPONENTS_PASSWORD_MANAGER_CORE_BROWSER_AFFILIATION_BACKEND_H_
