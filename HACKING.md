# Exploit track, rules and rewards

## Scope

The following are guidelines for what is eligible to a reward within this
hackathon or not.

### Explicitly out of scope

The following parts of the infrastructure and attack surface are explicitly out
of scope, as they are not the point of this hackathon, and preventing against
these types of attacks is better not our goal or expertise.

- Web interface (https://hacksat.dev) resource exhaustion:
  - denial of service of the web server
  - spam *of the web interface* in general (excessive account creation, image upload, deployment starts)

### In-scope

Everything that is not explicitly out of scope is by default considered
eligible. We still list explicitly a few interesting potential attack vectors
that we expect below, but the list is not exhaustive:

- On-board:
  - virtualization escape: read, write, or otherwise affect the host system or
      other unikernels. This includes exploitable side-channel attacks, or
      exploits of KVM/qemu/solo5 misconfigurations or obsolete versions
  - capabilities privilege escalation: access privileged capabilities without
      proper authentication
  - capabilities denial of service: provoking the crash or otherwise
      unresponsiveness of the capability manager, so that other unikernels
      cannot access it anymore
  - network isolation escape: interact with something else than the capability
      manager on the host, over the network. This includes other unikernels
      running on the same bridge.
- Server infiltration (gain foothold to web interface server, on-board
    computers, or in general our internal network)
- Web interface privilege escalation (gain admin permission)

## Transparency

Whether rewarded or not, all exploits in scope that are submitted will be
transparently published (and credited to their authors) in the final report.

## Rewards

Exploits that are in scope and confirmed to be applicable will be rewarded with
cash bounties, depending on their severity, novelty, and up to 10,000€, according to the
following guidelines (subject to the discretion of Parsimoni, and until the prize
pool is empty).

Note that if the same vulnerability is independently discovered and submitted by
multiple entities, only the **first** submission will be rewarded (but all
authors will be credited).

All rewards will be determined at the end of the submission period, so they can
be scaled according to the total number of submissions.

### Sandbox escape

Highest severity (~5000€). Reward will be scaled according to the complexity and novelty
of the approach (see above).

### Privilege escalation

High severity (~2000€). Severity will depend on the exploitability of the
escalation and its target (web interface, provider unikernel).

### Resource exhaustion

Low to medium severity (~200€+). Severity will depend on the consequences of the
denial of service: punctual restarts, long-term inavailability, influence on
other guests, etc. 

### Other

Subject to discussion with the authors.

